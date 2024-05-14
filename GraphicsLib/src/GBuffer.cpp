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

/// Hard-coded filepath to the g-buffer geometryvertex shader.
const std::string GBUF_GEO_VERT_SHADER_FILEPATH = "../../resources/shaders/gbuf-geo.vert";

/// Hard-coded filepath to the g-buffer geometry fragment shader.
const std::string GBUF_GEO_FRAG_SHADER_FILEPATH = "../../resources/shaders/gbuf-geo.frag";

/// Hard-coded filepath to the g-buffer lighting pass vertex shader.
const std::string GBUF_LIGHT_VERT_SHADER_FILEPATH = "../../resources/shaders/lighting-pass.vert";

/// Hard-coded filepath to the g-buffer lighting pass fragment shader.
const std::string GBUF_LIGHT_FRAG_SHADER_FILEPATH = "../../resources/shaders/gbuf-light.frag";

/// Naming convention for view matrix in shaders
const std::string VIEW_MAT_UNIFORM_NAME = "viewMat";

/// Naming convention for projection matrix in shaders
const std::string PROJ_MAT_UNIFORM_NAME = "projMat";

/// Uniform name for the "number of active lights" uniform in the
/// lighting pass fragment shader.
const std::string ACTIVE_LIGHTS_UNIFORM_NAME = "numActiveLights";



/**
 * Constructor
 * @param width width of the framebuffer in pixels
 * @param height height of the framebuffer in pixels
 */
GBuffer::GBuffer(WindowManager& window)
    :
    mWindow(window),
    mGeometryShaders("g-buffer geometry shaders",
                     GBUF_GEO_VERT_SHADER_FILEPATH.c_str(),
                     GBUF_GEO_FRAG_SHADER_FILEPATH.c_str()),
    mLightingShaders("g-buffer lighting shaders",
                     GBUF_LIGHT_VERT_SHADER_FILEPATH.c_str(),
                     GBUF_LIGHT_FRAG_SHADER_FILEPATH.c_str())

{
    // Grab the width an height of the window real quick
    auto size = window.GetWindowSize();
    auto width = size.first;
    auto height = size.second;

    glGenFramebuffers(1, &mGBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mGBuffer);

    // Check out how we use GL_RGBA16F as the internal format for
    // the position and normal color buffers--we need high precision!

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
    // not accidentally rendering to the wrong framebuffer."
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // Out of "courtesy," we'll initialize some uniforms in the shaders.

    // Geometry shaders:
    mGeometryShaders.use();
    // Projection matrix will likely never change, so we can set it here:
    auto projMat = mWindow.GetProjectionMatrix();
    mGeometryShaders.setMat4Uniform(PROJ_MAT_UNIFORM_NAME, projMat);

    // Lighting shaders:
    mLightingShaders.use();
    // Initialize the activeLights to zero:
    mLightingShaders.setIntUniform(ACTIVE_LIGHTS_UNIFORM_NAME, 0);



    // Initialize the screen-sized quad:
    // TODO

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
    // Bind this framebuffer
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mGPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mGNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mGAlbedoSpec);

    // Activate lighting shaders
    mLightingShaders.use();

    // Set directional light
    dirLight->SetLightingUniforms(mLightingShaders);

    // set lighting uniforms for each point light
    for(PointLight* ptLight : ptLights)
    {
        // The indices in the uniform array should all be ok,
        // since they were established when the scene was created!
        ptLight->SetLightingUniforms(mLightingShaders);
    }
    // make sure to set the sampler2D uniforms with the texture id's
    // including view position (camera position in world? -- or wait, no... it's 0,0,0 since I'm doing it in view space)

    // render quad to screen

}
