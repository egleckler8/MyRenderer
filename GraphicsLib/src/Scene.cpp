/**
 * @file Scene.cpp
 * @author Elijah Gleckler
 */

#include "Scene.h"

#include "PointLight.h"
#include "DirectionalLight.h"
#include "RenderObject.h"
#include "Skybox.h"

/// Uniform name for the "number of active lights" uniform in any
/// lighting shader that wants to render point lights
const std::string ACTIVE_PT_LIGHTS_UNIFORM_NAME = "numActivePtLights";

/// Naming convention for the directional light-skipping bool the lighting frag shader
const std::string DIRLIGHT_OPTIMIZER_BOOL_UNIFORM_NAME = "dirLightIsActive";


/**
 * Default constructor
 * (Does nothing...?)
 */
Scene::Scene()
{
/*
 * The g-buffer shaders will try to compute a directional light
 * regardless of whether the uniform struct is initialized.
 *
 * In GBuffer::LightingPass, Scene::GetDirectionalLight()->SetLightingUniforms
 * is called, which would be bad if GetDirectionalLight returned a nullptr.
 *
 * We could just say, "if (dirLight != nullptr), but then what would we do
 * if it is? The shader uniforms would not be set, meaning that GLSL would
 * try to access the uninitialized fields of the DirectionalLight uniform
 * (dirLight) when it does the lighting computations.
 *
 * So, my design choice is to make sure that Scene::mDirectionalLight is
 * never nullptr by initializing a default directional light with zero
 * Phong color and zero direction so that GLSL doesn't exhibit undefined
 * behavior.
 *
 * In this way, SetLightingUniforms will be successfully called on the
 * dirLight pointer in GBuffer::LightingPass, and they will all be set
 * to zero.
 *
 * However... I actually could save directional light computation on each
 * screen pixel (in deferred rendering) and a couple glUniform setting calls
 * per lighting pass if I had a boolean uniform like "dirLightIsActive." Then,
 * the shader could simply just skip that step and never touch the null values,
 * and GBuffer::LightingPass could skip the multi-uniform setting by seeing that
 * it's a nullptr.
 *
 * However, this would mostly just be valuable when there is no directional lighting
 * in a scene. I suspect that this would be pretty rare, so I won't try to implement
 * that optimization yet. I could see it coming in handy if the scene changed often
 * between above-ground and underground.
 *
 * I could make it so that only when the state of Scene::mDirectionalLight is updated
 * do we update the boolean "dirLightIsActive" in order to save many uniform setting
 * calls...
 *
 * However, the signal to update this would come from a higher-level part of the
 * engine, most likely somewhere in the game logic. It would require a call to
 * update GBuffer::mLightingShaders, so GBuffer would have to be informed.
 *
 * Well,I suppose that it would be nice if we could have this signal come from
 * a hypothetical "Scene::SetDirectionalLight(DirectionalLight* dirLight);"
 * (that might not be so hypothetical all so soon, lol...).
 *
 * How in the world could I, in a clean way, get to the GBuffer shaders
 * from this class? I wouldn't want to devise some big, hacky system
 * for such a little optimization...
 *
 * UPDATE:
 * I put in the optimization... now, users can set mDirectionalLight to
 * nullptr to signify an absence of directional light
 *
 */

}


/**
 * Make sure each point light knows its
 * index in the vector so it can set the
 * proper uniforms.
 *
 * We'll just do it linearly in the list, so that the
 * first item is shader index 0, etc.
 */
void Scene::UpdatePointLightIndices()
{
    for(int i = 0; i < mPointLights.size(); ++i)
    {
        auto light = mPointLights.at(i);
        light->SetShaderIndex(i);
    }
}




/**
 * Add a light source to the scene, making sure
 * it is aware of its index in the vector so it
 * can properly set its uniforms.
 *
 * @param lightSrc
 */
void Scene::AddPointLight(PointLight *lightSrc)
{
    mPointLights.push_back(lightSrc);
    UpdatePointLightIndices();
}



/**
 * Render all RenderObjects to the currently
 * bound framebuffer with a supplied set of
 * shaders so each RenderObject can set its
 * transformation uniforms.
 *
 * @param shaders Currently bound shaders
 */
void Scene::RenderObjects(ShaderProgram &shaders)
{
    // Render all the objects to the g-buffer
    for (RenderObject* object : mObjects)
    {
        // These two functions are decoupled intentionally so
        // that we only have to pass the view matrix to one
        object->SetTransformationUniforms(shaders);
        object->Draw(shaders);
    }
}



/**
 * Render lighting to the currently bound framebuffer.
 *
 * Doesn't really render anything... (right now)
 *
 * Just sets the lighting uniforms in the supplied shader.
 * For now, these will most likely be the GBuffer's
 * lighting shaders.
 *
 * @param shaders Shaders to set lighting uniforms
 */
void Scene::RenderLighting(ShaderProgram &shaders)
{
    // Set single directional light
    // However, it could be that there is no directional light.
    // SO heck and update the state of directional light activity
    if (CheckUpdateDirLightState(shaders))
    {
        mDirectionalLight->SetLightingUniforms(shaders);
    }

    // Set lighting uniforms for each point light
    for(PointLight* ptLight : mPointLights)
    {
        // The indices in the uniform array should all be ok,
        // since they were established when the scene was created!
        ptLight->SetLightingUniforms(shaders);
    }

    // Tell the shaders how many point lights to consider.
    // This will fail if the lighting shaders don't have this uniform!
    // It's a feature, not a bug... what I'm saying is, if you
    // want to render lighting anywhere, you need to make sure
    // the shaders know how many lights you want to render on
    // this pass. Also, all shaders that want to render lights
    // should have this same convention.
    shaders.SetIntUniform(ACTIVE_PT_LIGHTS_UNIFORM_NAME, mPointLights.size());
    // Will set the size when it's zero, and is called on
    // every render pass, so we should never hit an error.
}



/**
 * Render the skybox to the currently bound framebuffer.
 * Skybox will use its own shaders, but needs projection
 * and view matrices to draw.
 *
 * @param projMat projection matrix
 * @param viewMat view matrix
 */
void Scene::RenderSkybox(glm::mat4 projMat, glm::mat4 viewMat)
{
    if (mSkybox != nullptr)
    {
        mSkybox->Draw(projMat, viewMat);
    }
}



/**
 * Check whether the input directional light is valid
 * and update the state of the engine if it's not.
 *
 * Convenient because it checks the state of the input
 * the state that this class holds--which tells the
 * lighting shaders whether or not they should compute
 * directional lighting.
 *
 * Here is another choice by me, similar to the "num
 * ActivePtLights" thing: All shaders that want to
 * render a directional light will only try to render
 * one, and so there must be a uniform named ......
 * $DIRLIGHT_OPTIMIZER_BOOL_UNIFORM_NAME... for the
 * shaders to work.
 *
 * @param shaders Shaders we should tell whether there
 *                is a directional light to render
 * @return are we good to render directional light?
 */
bool Scene::CheckUpdateDirLightState(ShaderProgram &shaders)
{
    // This is an easy check...
    bool dirLightIsActive = (mDirectionalLight != nullptr);

    // Now, check if this is a state change from
    // what this class last remembers
    if (dirLightIsActive != mDirLightIsActive)
    {
        // Swap the state, ...
        mDirLightIsActive = dirLightIsActive;
        // ... and tell the lighting shader about it!
        shaders.SetBoolUniform(DIRLIGHT_OPTIMIZER_BOOL_UNIFORM_NAME,
                                        mDirLightIsActive);

    }
    // Else...
    // The current state is the same as the recorded state,
    // so there is nothing to update/worry about.
    // We'll return whether it's active or not, then the
    // lighting pass will or will not render the directional
    // light, as expected.

    return mDirLightIsActive;
}
