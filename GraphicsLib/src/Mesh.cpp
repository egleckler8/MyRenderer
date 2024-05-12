/**
 * @file Mesh.cpp
 * @author Elijah Gleckler
 */

#include "glad/glad.h"

#include "Mesh.h"
#include "Texture2D.h"
#include "Shader.h"

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

    // Bind the VAO and then VBO, so we can set up the structure
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


/**
 * Renders this mesh and its textures using the
 * provided shader program
 *
 * @param shaders ShaderProgram program with which to render this mesh
 */
void Mesh::Render(std::shared_ptr<ShaderProgram> shaders)
{

    // Set the texture uniforms in the shader
    // textures associated with materials?

    // LearnOpenGL's naming conventions... pg. 163
    unsigned int diffuseNum = 1;
    unsigned int specularNum = 1;
    unsigned int roughnessNum = 1;

    for (unsigned int i = 0; i < mTextures.size(); ++i)
    {
        // activate the texture unit
        glActiveTexture(GL_TEXTURE0 + i);

        // We're going to get the data needed to set the shader uniform
        // with the naming convention that LearnOpenGL came up with
        TextureType type = mTextures[i].type;
        std::string number;
        std::string uniformName = "material.texture_"; // assume it's in a material struct

        // retrieve texture number (the N in diffuse_textureN)
        if (type == TextureType::Diffuse)
        {
            number = std::to_string(diffuseNum++);
            uniformName += "diffuse_" + number;
        }
        else if (type == TextureType::Specular)
        {
            number = std::to_string(specularNum++);
            uniformName += "specular_" + number;
        }
        else if (type == TextureType::Roughness)
        {
            number = std::to_string(roughnessNum++);
            uniformName += "roughness_" + number;
        }

        // Set the uniform to this texture number, assuming it's in the material struct
        shaders->use(); // I suppose we should assure this, even though it was
                        // likely already called in RenderObject::Render
        shaders->set1FUniform(uniformName.c_str(), i);

        glBindTexture(GL_TEXTURE_2D, mTextures[i].id);

    }
    glActiveTexture(0);

    // draw the mesh!
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

