/**
 * @file GBuffer.h
 * @author Elijah Gleckler
 *
 * A g-buffer for deferred shading.
 *
 * Basically stores the state of the g-buffer
 * and has functions for rendering a scene
 * to the g-buffer & drawing it to the
 * default framebuffer/screen
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_GBUFFER_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_GBUFFER_H

#include "ShaderProgram.h"
#include "FullscreenQuad.h"


class WindowManager;
class RenderObject;
class PointLight;
class DirectionalLight;
class Scene;
/**
 * A g-buffer for deferred shading.
 */
class GBuffer
{
private:

    /// OpenGl id of the framebuffer for the g-buffer
    unsigned int mGBuffer;

    /// Position texture GL id
    unsigned int mGPosition;

    /// Normal texture GL id
    unsigned int mGNormal;

    /// Combined color/specular value texture GL id
    unsigned int mGAlbedoSpec;

    /// GL id of the renderbuffer holder depth and stencil data
    unsigned int mDepthStencilBuf;

    /// The screen-sized quad we'll render to
    FullscreenQuad mFullscreenQuad;

    /// Shader program for geometry pass
    ShaderProgram mGeometryShaders;

    /// Shader program for lighting pass
    ShaderProgram mLightingShaders;

    /// The window we'll render to
    WindowManager& mWindow;

    void GeometryPass(Scene &scene);
    void LightingPass(Scene& scene);

public:

    GBuffer(WindowManager& window);

    /// Default constructor (disabled)
    GBuffer() = delete;

    /// Copy constructor (disabled)
    GBuffer(const GBuffer &) = delete;

    /// Assignment operator
    void operator=(const GBuffer &) = delete;

    // ****************************************************************

    void RenderScene(Scene& scene);



};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_GBUFFER_H
