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

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

/// Hard-coded filepath to the g-buffer geometry vertex shader.
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

/// Uniform name for the view position in the lighting pass shaders
const std::string VIEW_POS_UNIFORM_NAME = "viewPos";

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

    // Grab the scrWidth and scrHeight of the window real quick
    auto size = window.GetWindowSize();
    auto scrWidth = size.first;
    auto scrHeight = size.second;

    // Generate & bind a framebuffer for the g-buffer
    glGenFramebuffers(1, &mGBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mGBuffer);

    // Position color buffer
    glGenTextures(1, &mGPosition);
    glBindTexture(GL_TEXTURE_2D, mGPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scrWidth, scrHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mGPosition, 0);

    // Normal color buffer
    glGenTextures(1, &mGNormal);
    glBindTexture(GL_TEXTURE_2D, mGNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scrWidth, scrHeight, 0, GL_RGBA, GL_FLOAT, NULL);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, scrWidth, scrHeight, 0, GL_RGBA, GL_FLOAT, NULL);
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
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scrWidth, scrHeight);
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

    // yeah
    glDepthFunc(GL_LEQUAL);

    // Out of "courtesy," we'll initialize some uniforms in the shaders,
    // so we don't have to repeatedly & redundantly do it at runtime

    // Geometry shaders:
    mGeometryShaders.use();

    // Projection matrix will likely never change, so we can set it here
    //auto projMat = mWindow.GetProjectionMatrix();
    glm::mat4 projMat = glm::perspective(glm::radians(45.0f),
                               (float)scrWidth / scrHeight, 0.1f, 100.0f);
    mGeometryShaders.SetMat4Uniform(PROJ_MAT_UNIFORM_NAME, projMat);

    // Lighting shaders:
    mLightingShaders.use();

    // Set the sampler2D uniforms with the texture unit numbers
    // (above at " *** Remember this convention! *** ")
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
    GeometryPass(scene);
    LightingPass(scene);
    SkyboxPass(scene);
}



/**
 * BindTextures the geometry pass
 * BindTextures all geo/color data to the g-buffer
 *
 * @param scene List of objects whose color/geometry data we want
 */
void GBuffer::GeometryPass(Scene &scene)
{
    // Bind the g-buffer
    glBindFramebuffer(GL_FRAMEBUFFER, mGBuffer);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Get the transformation matrices from the window & set uniforms
    auto viewMat = mWindow.GetCamera()->GetViewMatrix();

    // Render all objects
    mGeometryShaders.use();
    mGeometryShaders.SetMat4Uniform(VIEW_MAT_UNIFORM_NAME, viewMat);
    scene.RenderObjects(mGeometryShaders);

}



/**
 * BindTextures the lighting pass
 * Use the geo data in the g-buffer to calculate lighting
 */
void GBuffer::LightingPass(Scene& scene)
{
    // Re-bind default framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate lighting shaders
    mLightingShaders.use();

    // Set view position to the camera position
    auto camPos = mWindow.GetCamera()->GetPosition();
    mLightingShaders.SetVec3Uniform(VIEW_POS_UNIFORM_NAME, camPos);

    // bind all g-buffer textures
    glActiveTexture(GL_TEXTURE0 + POSITION_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, mGPosition);
    glActiveTexture(GL_TEXTURE0 + NORMAL_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, mGNormal);
    glActiveTexture(GL_TEXTURE0 + ALBEDOSPEC_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, mGAlbedoSpec);

    // Texture uniforms are already set in the constructor,
    // since they will not change per render loop iteration.

    // Tell the scene to "render lighting" (set lighting unis)
    scene.RenderLighting(mLightingShaders);

    // With textures bound and lighting shaders active,
    // draw the fullscreen quad to the default framebuffer!
    mFullscreenQuad.Draw();
}



/**
 * Do a stencil test and render the skybox
 * @param scene Scene with the skybox data
 */
void GBuffer::SkyboxPass(Scene &scene)
{

    // Blit frambuffer with g-buffer depth and default buffer color
    // for post-deferred pipeline (skybox?)
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mGBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, 1000, 800, 0, 0, 1000, 800, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Render skybox;
    // TODO figure out a cleaner way to give the projmat to skybox??
    scene.RenderSkybox(mWindow.GetProjectionMatrix(), mWindow.GetCamera()->GetViewMatrix());
    // TODO... i think this just won't work in a deferred system now,
    // just like how blending won't work. gotta look into this.

}
