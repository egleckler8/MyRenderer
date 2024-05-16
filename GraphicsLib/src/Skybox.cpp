/**
 * @file Skybox.cpp
 * @author Elijah Gleckler
 */

#include <iostream>

#include "Skybox.h"

#include <glad/glad.h>
#include <stb_image.h>

/// Naming convention for the positive x direction (world) face
const std::string POS_X_IMG_NAME = "pos_x.jpg";

/// Naming convention for the negative x direction (world) face
const std::string NEG_X_IMG_NAME = "neg_x.jpg";

/// Naming convention for the positive x direction (world) face
const std::string POS_Y_IMG_NAME = "pos_y.jpg";

/// Naming convention for the positive x direction (world) face
const std::string NEG_Y_IMG_NAME = "neg_y.jpg";

/// Naming convention for the positive x direction (world) face
const std::string POS_Z_IMG_NAME = "pos_z.jpg";

/// Naming convention for the positive x direction (world) face
const std::string NEG_Z_IMG_NAME = "neg_z.jpg";

/// Slap names in an array so we can iterate over it
const char* IMG_NAMES[] = {
    POS_X_IMG_NAME.c_str(),
    NEG_X_IMG_NAME.c_str(),
    POS_Y_IMG_NAME.c_str(),
    NEG_Y_IMG_NAME.c_str(),
    POS_Z_IMG_NAME.c_str(),
    NEG_Z_IMG_NAME.c_str()
};

/// Vertices for rendering a cubemap
constexpr float CUBEMAP_VERTICES[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

/// Hardcoded filepath to the simple, skybox vertex shader
const std::string SKYBOX_VERT_SHADER_FILEPATH = "../resources/shaders/skybox.vert";

/// Hardcoded filepath to the simple, skybox fragment shader
const std::string SKYBOX_FRAG_SHADER_FILEPATH = "../resources/shaders/skybox.frag";

/// Uniform name for the projection matrix in shaders
const std::string SKYBOX_SHADERS_PROJMAT_UNIFORM_NAME = "projMat";

/// Uniform name for the view matrix in shaders
const std::string SKYBOX_SHADERS_VIEWMAT_UNIFORM_NAME = "viewmat";

/// Uniform name for the samplerCube cubemap sampler in the frag shader
const std::string CUBEMAP_TEX_UNIFORM_NAME = "skyboxTex";




/**
 * Constructor.
 * @param faceTexDir Vector with the file directory for the cube faces
 */
Skybox::Skybox(const std::string &faceTexDir)
:
mTextureID(LoadCubeMap(faceTexDir)),
mSkyboxShaders("skybox shaders",
               SKYBOX_VERT_SHADER_FILEPATH.c_str(),
               SKYBOX_FRAG_SHADER_FILEPATH.c_str())

{

    // Set up the VAO
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    // Bind the VAO and then VBO, so we can set up the structure
    glBindVertexArray(mVAO);

    // Make space for the vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBEMAP_VERTICES), &CUBEMAP_VERTICES, GL_STATIC_DRAW);

    // Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

    // Unbind
    glBindVertexArray(0);


    // Set the cubemap texture uniform in the shaders (texture unit 0)
    mSkyboxShaders.SetIntUniform(CUBEMAP_TEX_UNIFORM_NAME, 0);


}


/**
 * Builds a cubemap from the file directory containing the six
 * face textures. Images must follow a specific naming convention,
 * in order to enforce consistency among different cube maps.
 *
 * I thought this convention might be a good way to make me
 * think about which face goes to which if I were to ever
 * download a cube map texture or make my own.
 *
 * @param faceTexDir directory with the face texture images
 * @return glId of the loaded texture
 */
unsigned int Skybox::LoadCubeMap(const std::string &faceTexDir)
{
    unsigned int textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Load each of the face images, one at a time

    // Put 'em together
    int width, height, numChannels;
    for(int i = 0; i < 6; ++i)
    {
        std::string fullFp = (faceTexDir + '/' + IMG_NAMES[i]);

        // Load the image
        unsigned char* imgData = stbi_load(fullFp.c_str(), &width, &height,
                                           &numChannels, 0);

        if (imgData)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
        }
        else
        {
            std::cout << "Failed to load cubemap texture: " << IMG_NAMES[i] << std::endl;
        }

        stbi_image_free(imgData);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);

    return textureID;
}


/**
 * Draw the cubemap to the currently bound framebuffer
 *
 * @param projMat projection matrix to use in shaders
 * @param viewMat view matrix to use in shaders
 */
void Skybox::Draw(glm::mat4 projMat, glm::mat4 viewMat)
{
    // Modify the viewmat to remove the translation portion
    viewMat = glm::mat4(glm::mat3(viewMat));

    // Set transformation uniforms
    mSkyboxShaders.use();
    mSkyboxShaders.SetMat4Uniform(SKYBOX_SHADERS_PROJMAT_UNIFORM_NAME, projMat);
    mSkyboxShaders.SetMat4Uniform(SKYBOX_SHADERS_VIEWMAT_UNIFORM_NAME, viewMat);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureID);

    glDepthMask(GL_FALSE);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}


