/**
 * @file FullscreenQuad.cpp
 * @author Elijah Gleckler
 */
#include <glad/glad.h>
#include "FullscreenQuad.h"

/// Vertices for a fullscreen quad in NDC (normalized device coords)
constexpr float FULLSCREEN_QUAD_VERTICES[] = {
    // Positions   // TexCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};


/**
 * Constructor.
 * Sets up the VAO and VBO
 */
FullscreenQuad::FullscreenQuad()
{
    // Create buffers for our members
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    // Bind the VAO and then VBO, so we can set up the structure
    glBindVertexArray(mVAO);

    // Make space for the vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(FULLSCREEN_QUAD_VERTICES), &FULLSCREEN_QUAD_VERTICES, GL_STATIC_DRAW);

    //
    // Vertex attribute pointers:
    //

    // Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float )));

    // Unbind
    glBindVertexArray(0);

}



/**
 * Draw the quad to whatever is currently bound.
 *
 * Hopefully, it's a shader program whose vertex
 * shader expects an input from a vbo like above...
 * That is,:
 *
 * layout (location = 0) in vec2 aPos;
 * layout (location = 1) in vec2 aTexCoords;
 *
 */
void FullscreenQuad::Draw()
{
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
