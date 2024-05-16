/**
 * @file Skybox.h
 * @author Elijah Gleckler
 *
 * Skybox on a cubemap texture on a cube
 * with dimensions [1.0, -1.0]^3
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_SKYBOX_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_SKYBOX_H

#include "ShaderProgram.h"
/**
 * Skybox on a cubemap texture on a cube
 * with dimensions [1.0, -1.0]^3
 */
class Skybox
{
private:

    /// GL id of the texture
    unsigned int mTextureID;

    /// VAO for rendering
    unsigned int mVAO;

    /// VBO for rendering
    unsigned int mVBO;

    ShaderProgram mSkyboxShaders;

    unsigned int LoadCubeMap(const std::string &faceTexDir);

public:

    // Constructor
    explicit Skybox(const std::string &faceTexDir);

    /// Default constructor (disabled)
    Skybox() = delete;

    /// Copy constructor (disabled)
    Skybox(const Skybox &) = delete;

    /// Assignment operator
    void operator=(const Skybox &) = delete;

    // ****************************************************************

    void Draw(glm::mat4 projMat, glm::mat4 viewMat);

};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_SKYBOX_H
