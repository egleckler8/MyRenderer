/**
 * @file Mesh.h
 * @author Elijah Gleckler
 *
 * A mesh of vertices
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


class Shader;
/**
 * A mesh of vertices
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

    /// OpenGL ID of the ertex buffer object for this mesh
    unsigned int mVBO;

    /// OpenGL ID of the element buffer object for this mesh
    unsigned int mEBO;

    void SetUpMesh();

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


    void Render(std::shared_ptr<Shader> shaders);

};

#endif //LEARNING_OPENGL__MESH_H