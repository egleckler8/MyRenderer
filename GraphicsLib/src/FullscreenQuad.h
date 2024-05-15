/**
 * @file FullscreenQuad.h
 * @author Elijah Gleckler
 *
 * Stores the data for a fullscreen quad.
 *
 * Instead of deriving something from Mesh and
 * forcing it into the inheritance tree, I have
 * chosen to make a fresh, new class so that we
 * can focus on rendering a screen quad as quickly
 * and simply as possible.
 *
 * So, this class is not related at all to the
 * other quad class, even though there's a good
 * amount of redundancy. I should probably do something
 * about that...
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SCREENFILLQUAD_H
#define LEARNING_OPENGL_GRAPHICSLIB_SCREENFILLQUAD_H

/**
 * Stores the data for a fullscreen quad.
 */
class FullscreenQuad
{
private:

    /// OpenGL ID of the vertex attribute object for this mesh
    unsigned int mVAO;

    /// OpenGL ID of the vertex buffer object for this mesh
    unsigned int mVBO;

public:

    FullscreenQuad();
    // copy, assign, and default construct all you want!

    void Draw();

};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SCREENFILLQUAD_H
