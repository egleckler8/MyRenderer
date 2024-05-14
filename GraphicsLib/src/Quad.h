/**
 * @file Quad.h
 * @author Elijah Gleckler
 *
 * A simplified mesh that is just a quad.
 *
 * Can be 2D or 3D. Must specify at construction.
 */


enum QuadType
{
    Quad2D,
    Quad3D
};

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_QUAD_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_QUAD_H

#include "Mesh.h"
#include "quad_vertices.h"

/**
 * A simplified mesh that is just a quad.
 * Quads will be -1.0 to 1.0 in model space
 */
class Quad : public Mesh
{
private:

public:

    /**
     * Constructor for a 2D quad
     * @param dimensions Dimensions, width by height in model space
     * @param textures List of all this quad's textures
     */
    Quad(glm::vec2 dimensions, std::vector<TextureData> textures)
        : Mesh(SquareVertices(), SquareIndices(), textures) {}


    /**
     * Constructor for a 3D quad
     * @param dimensions Dimensions, width by height in model space
     * @param textures List of all this quad's textures
     */
    Quad(glm::vec3 dimensions, std::vector<TextureData> textures)
        : Mesh(CubeVertices(), CubeIndices(), textures) {}

    /// Default constructor (disabled)
    Quad() = delete;

    /// Copy constructor (disabled)
    Quad(const Quad &) = delete;

    /// Assignment operator
    void operator=(const Quad &) = delete;

    // ****************************************************************



};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_QUAD_H
