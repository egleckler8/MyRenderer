/**
 * @file Mesh.h
 * @author Elijah Gleckler
 *
 * A mesh of vertices
 *
 * Assimp makes sure there is only one material
 * per mesh, so we'll be good to draw with indexing
 * once this is loaded by the Model class!
 *
 * This reddit thread was very helpful in my understanding
 * of Assimp and rendering and stuff and helped me realize
 * to check about materials and meshes, etc. whatever:
 *
 * https://www.reddit.com/r/opengl/comments/4jwj9n/single_mesh_multiple_materials/
 *
 */

#ifndef LEARNING_OPENGL__MESH_H
#define LEARNING_OPENGL__MESH_H

#include <glm.hpp>
#include <vector>

#include "Texture2D.h"


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};


class ShaderProgram;
/**
 * A mesh of vertices. Only one material!
 */
class Mesh
{
private:

    /// Vertices of this mesh
    std::vector<Vertex> mVertices;

    /// Indices of the vertices so we can draw with EBO
    std::vector<unsigned int> mIndices;

    /// Textures of this mesh
    std::vector<TextureData> mTextures;

    /// OpenGL ID of the vertex attribute object for this mesh
    unsigned int mVAO;

    /// OpenGL ID of the vertex buffer object for this mesh
    unsigned int mVBO;

    /// OpenGL ID of the element buffer object for this mesh
    unsigned int mEBO;

    void BindTextures(ShaderProgram &shaders);

public:

    // Constructor
    Mesh(   std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<TextureData> textures);

    /// Default constructor (disabled)
    Mesh() = delete;

    /// Copy constructor (disabled)
    Mesh(const Mesh &) = delete;

    /// Assignment operator
    void operator=(const Mesh &) = delete;

    void Draw(ShaderProgram &shaders);

};

#endif //LEARNING_OPENGL__MESH_H
