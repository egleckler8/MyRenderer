/**
 * @file GBuffer.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <glad/glad.h>
#include "GBuffer.h"

#include "RenderObject.h"
#include "WindowManager.h"
#include "Camera.h"
#include "Scene.h"
#include "PointLight.h"
#include "DirectionalLight.h"

/// Hard-coded filepath to the g-buffer geometryvertex shader.
const std::string GBUF_GEO_VERT_SHADER_FILEPATH = "../resources/shaders/gbuf-geo.vert";

/// Hard-coded filepath to the g-buffer geometry fragment shader.
const std::string GBUF_GEO_FRAG_SHADER_FILEPATH = "../resources/shaders/gbuf-geo.frag";

/// Hard-coded filepath to the g-buffer lighting pass vertex shader.
const std::string GBUF_LIGHT_VERT_SHADER_FILEPATH = "../resources/shaders/gbuf-light.vert";

/// Hard-coded filepath to the g-buffer lighting pass fragment shader.
const std::string GBUF_LIGHT_FRAG_SHADER_FILEPATH = "../resources/shaders/gbuf-light.frag";

/// Naming convention for view matrix in shaders
const std::string VIEW_MAT_UNIFORM_NAME = "viewMat";

/// Naming convention for projection matrix in shaders
const std::string PROJ_MAT_UNIFORM_NAME = "projMat";

/// Naming convention for the directional light-skipping bool the lighting frag shader
const std::string DIRLIGHT_OPTIMIZER_BOOL_UNIFORM_NAME = "dirLightIsActive";

/// Uniform name for the "number of active lights" uniform in the
/// lighting pass fragment shader.
const std::string ACTIVE_LIGHTS_UNIFORM_NAME = "numActiveLights";

/// Uniform name for the position texture in the lighting pass frag shader
const std::string POSITION_TEX_UNIFORM_NAME = "gPosition";

/// Uniform name for the normal texture in the lighting pass frag shader
const std::string NORMAL_TEX_UNIFORM_NAME = "gNormal";

/// Uniform name for the albedo texture in the lighting pass frag shader
const std::string ALBEDOSPEC_TEX_UNIFORM_NAME = "gAlbedoSpec";

/// Texture unit that the position texture will always be bound to
const unsigned int POSITION_TEX_UNIT = 0;

/// Texture unit that the normal texture will always be bound to
const unsigned int NORMAL_TEX_UNIT = 1;

/// Texture unit that the albedo texture will always be bound to
const unsigned int ALBEDOSPEC_TEX_UNIT = 2;



/**
 * Constructor
 * @param width width of the framebuffer in pixels
 * @param height height of the framebuffer in pixels
 */
GBuffer::GBuffer(WindowManager& window)
    :
    mWindow(window),
    mFullscreenQuad(),
    mGeometryShaders("g-buffer geometry shaders",
                     GBUF_GEO_VERT_SHADER_FILEPATH.c_str(),
                     GBUF_GEO_FRAG_SHADER_FILEPATH.c_str()),
    mLightingShaders("g-buffer lighting shaders",
                     GBUF_LIGHT_VERT_SHADER_FILEPATH.c_str(),
                     GBUF_LIGHT_FRAG_SHADER_FILEPATH.c_str())

{

    // Grab the width and height of the window real quick
    auto size = window.GetWindowSize();
    auto width = size.first;
    auto height = size.second;

    // Generate & bind a framebuffer for the g-buffer
    glGenFramebuffers(1, &mGBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mGBuffer);

    // Position color buffer
    glGenTextures(1, &mGPosition);
    glBindTexture(GL_TEXTURE_2D, mGPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mGPosition, 0);

    // Normal color buffer
    glGenTextures(1, &mGNormal);
    glBindTexture(GL_TEXTURE_2D, mGNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mGNormal, 0);
    // Check out how we used GL_RGBA16F as the internal format for
    // the position and normal color buffers--we need high precision!

    // Diffuse/albedo & specular color buff
    // The RGB part is the diffuse/albedo color and
    // the A part is the specular intensity!
    glGenTextures(1, &mGAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, mGAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mGAlbedoSpec, 0);

    // Tell OpenGL which attachments we'll use
    unsigned int attachments[3] = {
        GL_COLOR_ATTACHMENT0, // position
        GL_COLOR_ATTACHMENT1, // normal
        GL_COLOR_ATTACHMENT2 // color (albedo + spec)
    };

    glDrawBuffers(3, attachments);

    // Depth and stencil buffers
    // Stored in a render buffer
    glGenRenderbuffers(1, &mDepthStencilBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthStencilBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    // Attach it to the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthStencilBuf);

    // Make sure it's all good!
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" <<
                  std::endl;

    // "Be sure to unbind the framebuffer to make sure we’re
    // not accidentally rendering to the wrong framebuffer." --LearnOpenGL pg. ??
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Out of "courtesy," we'll initialize some uniforms in the shaders,
    // so we don't have to repeatedly & redundantly do it at runtime

    // Geometry shaders:
    mGeometryShaders.use();

    // Projection matrix will likely never change, so we can set it here
    auto projMat = mWindow.GetProjectionMatrix();
    mGeometryShaders.setMat4Uniform(PROJ_MAT_UNIFORM_NAME, projMat);

    // Lighting shaders:
    mLightingShaders.use();

    // Initialize the activeLights to zero to avoid accessing nullptr
    mLightingShaders.SetIntUniform(ACTIVE_LIGHTS_UNIFORM_NAME, 0);

    // Set the sampler2D uniforms with the texture unit numbers
    // (above at " *** Remember this convention! *** "
    // These will not change per render loop, so I figure I can
    // set them here to save 3 set uniform calls
    mLightingShaders.SetIntUniform(POSITION_TEX_UNIFORM_NAME, POSITION_TEX_UNIT);
    mLightingShaders.SetIntUniform(NORMAL_TEX_UNIFORM_NAME, NORMAL_TEX_UNIT);
    mLightingShaders.SetIntUniform(ALBEDOSPEC_TEX_UNIFORM_NAME, ALBEDOSPEC_TEX_UNIT);

}



/**
 * Render a scene full of RenderObjects and lights to the g-buffer
 * @param scene Scene (filled with objects and lights) to render
 */
void GBuffer::RenderScene(Scene &scene)
{
    GeometryPass(scene.GetRenderObjects());
    LightingPass(scene.GetPointLights(), scene.GetDirectionalLight());
}



/**
 * BindTextures the geometry pass
 * BindTextures all geo/color data to the g-buffer
 *
 * @param objects List of objects whose color/geometry data we want
 */
void GBuffer::GeometryPass(std::vector<RenderObject*> &objects)
{
    // Bind the g-buffer
    glBindFramebuffer(GL_FRAMEBUFFER, mGBuffer);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate the shaders before we pass them around!
    mGeometryShaders.use();

    // Get the transformation matrices from the window & set uniforms
    auto viewMat = mWindow.GetCamera()->GetViewMatrix();
    mGeometryShaders.setMat4Uniform(VIEW_MAT_UNIFORM_NAME, viewMat);

    // Render all the objects to the g-buffer
    for (RenderObject* object : objects)
    {
        // These two functions are decoupled intentionally so
        // that we only have to pass the view matrix to one
        object->SetTransformationUniforms(mGeometryShaders, viewMat);
        object->Draw(mGeometryShaders);
    }

}



/**
 * BindTextures the lighting pass
 * Use the geo data in the g-buffer to calculate lighting
 */
void GBuffer::LightingPass(std::vector<PointLight *> &ptLights,
                           DirectionalLight *dirLight)
{
    // Re-bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind all g-buffer textures
    glActiveTexture(GL_TEXTURE0 + POSITION_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, mGPosition);
    glActiveTexture(GL_TEXTURE0 + NORMAL_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, mGNormal);
    glActiveTexture(GL_TEXTURE0 + ALBEDOSPEC_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, mGAlbedoSpec);

    // Activate lighting shaders
    mLightingShaders.use();

    // Set single directional light
    // However, it could be that there is no directional light.
    // SO heck and update the state of directional light activity
    if (CheckUpdateDirLightState(dirLight))
    {
        dirLight->SetLightingUniforms(mLightingShaders);
    }

    // set lighting uniforms for each point light
    for(PointLight* ptLight : ptLights)
    {
        // The indices in the uniform array should all be ok,
        // since they were established when the scene was created!
        ptLight->SetLightingUniforms(mLightingShaders);
    }

    // Texture uniforms are already set in the constructor,
    // since they will not change per render loop iteration.

    // Set view position to the camera position??
    // TODO??

    // With textures bound and lighting shaders active,
    // draw the fullscreen quad to the default framebuffer!
    mFullscreenQuad.Draw();

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
 * @param dirLight Pointer to direcional light we'll check
 * @return Bool - "the directional light is valid"
 */
bool GBuffer::CheckUpdateDirLightState(DirectionalLight *dirLight)
{
    // This is an easy check...
    bool dirLightIsActive = (dirLight != nullptr);

    // Now, check if this is a state change from
    // what this class last remembers
    if (dirLightIsActive != mDirLightIsActive)
    {
        // Swap the state, ...
        mDirLightIsActive = dirLightIsActive;
        // ... and tell the lighting shader about it!
        mLightingShaders.SetBoolUniform(DIRLIGHT_OPTIMIZER_BOOL_UNIFORM_NAME,
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
