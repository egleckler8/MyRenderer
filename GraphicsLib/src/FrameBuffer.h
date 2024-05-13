/**
 * @file FrameBuffer.h
 * @author Elijah Gleckler
 *
 * A framebuffer
 *
 * The goal is to do some offscreen rendering
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_FRAMEBUFFER_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_FRAMEBUFFER_H

class FrameBuffer
{
private:

    /// OpenGl id of the framebuffer
    unsigned int mFramebuffer;

public:

    FrameBuffer(int width, int height);

    /// Default constructor (disabled)
    FrameBuffer() = delete;

    /// Copy constructor (disabled)
    FrameBuffer(const FrameBuffer &) = delete;

    /// Assignment operator
    void operator=(const FrameBuffer &) = delete;

    // ****************************************************************



};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_FRAMEBUFFER_H
