/**
 * @file Scene.cpp
 * @author Elijah Gleckler
 */

#include "Scene.h"

#include "PointLight.h"
#include "DirectionalLight.h"

/**
 * Default constructor
 *
 * The only thing we do here is initialize a blank
 * directional light that will have no effect on the scene.
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
