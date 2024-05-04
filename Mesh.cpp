/**
 * @file Mesh.cpp
 * @author Elijah Gleckler
 */

#include <glad/glad.h>

#include "Mesh.h"
#include "Texture2D.h"

/**
 * Constructor
 * @param vertices vector of vertices for this mesh
 * @param indices vector of vertex drawing order indices for this mesh
 * @param textures vector of textures for this mesh
 */
Mesh::Mesh( std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<TextureData> textures)
            :
            mVertices(vertices),
            mIndices(indices),
            mTextures(textures)
{
    // This will initialize the VAO, VBO, EBO--never fear
    SetUpMesh();
}

/**
 * Take the member mesh data and set that baby up (duh).
 * Initializes all the OpenGL things, like VAO, VBO, EBO.
 */
void Mesh::SetUpMesh()
{

    // Create buffers for our members
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    // Bind the VAO and then VBO so we can set up the structure
    glBindVertexArray(mVAO);

    // Make space for the vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

    // Make space for the drawing indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

    //
    // Vertex attribute pointers:
    //

    // Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    // Unbind
    glBindVertexArray(0);

}



void Mesh::Draw(Shader &shader)
{

    // Set the texture uniforms in the shader
    // textures associated with materials?



}

