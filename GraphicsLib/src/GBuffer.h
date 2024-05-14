/**
 * @file GBuffer.h
 * @author Elijah Gleckler
 *
 * A g-buffer for deferred shading.
 *
 * Basically stores the state of the g-buffer
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_GBUFFER_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_GBUFFER_H

#include "Quad.h"
#include "ShaderProgram.h"
/**
 * A g-buffer for deferred shading.
 */
class GBuffer
{
private:

    /// OpenGl id of the framebuffer for the g-buffer
    unsigned int mGBuffer;

    /// The screen-sized quad we'll render to
    //Quad mQuad;

    /// Shader program for geometry pass
    //ShaderProgram mGeometryShaders;

    /// Shader program for lighting pass
    //ShaderProgram mLightingShaders;

public:

    GBuffer(int width, int height);

    /// Default constructor (disabled)
    GBuffer() = delete;

    /// Copy constructor (disabled)
    GBuffer(const GBuffer &) = delete;

    /// Assignment operator
    void operator=(const GBuffer &) = delete;

    // ****************************************************************



};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_GBUFFER_H
