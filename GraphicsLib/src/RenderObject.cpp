/**
 * @file RenderObject.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <gtc/matrix_transform.hpp>

#include "RenderObject.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "LightSource.h"

/// Maximum number of light sources each shader should
/// deal with at a time.
const unsigned int MAX_LIGHTS_PER_SHADER = 16;

const std::string MODEL_MAT_UNIFORM_NAME = "modelMat";  ///< Naming convention for model matrix in shaders
const std::string NORMAL_MAT_UNIFORM_NAME = "normalMat"; ///< Naming convention for normal matrix in shaders


/**
 * Constructor
 *
 * - - - - - - - - - - WARNING: - - - - - - - - - - - - - - - - -
 *  You'd better make sure that the shader program
 *  supplied to the constructor fits with the textures
 *  stored in the model! The when Model::RenderScene is called,
 *  it will invoke the shader program and try to bind
 *  textures. It's on the shader programmer on modeling
 *  artist to coordinate this (the way things are now, at least)
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * @param model 3D model of the object
 * @param shaders shader program with which toto render the object
 */
RenderObject::RenderObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaders)
    : mModel(std::move(model)), mShaders(std::move(shaders))
{
    // Default model matrix at the origin
    // with scale 1.0 and no rotation
    UpdateModelMatrix();
}






/**
 * Set the shader uniforms corresponding to the transformation
 * matrices that this render object knows about, which is pretty
 * much just its own model matrix.
 *
 * The g-buffer or someone else should do the rest...
 *
 * Makes sure this RenderObject is in the right place in the final scene!
 *
 * @param shaders Currently bound shader program in which to set the uniforms
 * @param viewMatrix View matrix so we can compute the normal matrix
 *                   for this object and set the shaders.
 */
void RenderObject::SetTransformationUniforms(ShaderProgram &shaders,
                                             const glm::mat4 &viewMatrix)
{
    if (mModel != nullptr)
    {
        // Update the model matrix based on our current
        // position, rotation, and scale
        UpdateModelMatrix();

        // Model-View matrix and Normal Matrix
        // glm::mat4 modelViewMat = viewMatrix * mModelMatrix;
        glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(mModelMatrix)));

        // Set the transformation uniforms
        shaders.SetMat4Uniform(MODEL_MAT_UNIFORM_NAME, mModelMatrix);
        shaders.setMat3Uniform(NORMAL_MAT_UNIFORM_NAME, normalMat);

    }
    else
    {
        throw std::runtime_error("Be careful! Cannot render an instance with uninitialized assets.\n"
                                 "(RenderObject.cpp line 102)");
    }

}


/**
 * Draw the object to the currently bound framebuffer.
 *
 * Make sure SetTransformationUniforms is called to make
 * sure that the object is in the right place!
 *
 * @param shaders Currently bound shader program that the
 *                model will use to set textures uniforms
 */
void RenderObject::Draw(ShaderProgram &shaders)
{
    mModel->Draw(shaders);
}



/**
 * Updates the model matrix based on the current
 * data members storing the position, rotation,
 * and scale of the object.
 */
void RenderObject::UpdateModelMatrix()
{
    glm::mat4 modelMat(1.0f);
    modelMat = glm::translate(modelMat, mPosition);
    modelMat = glm::rotate(modelMat, mRotation.first, mRotation.second);
    modelMat = glm::scale(modelMat, mScale);
    mModelMatrix = modelMat;
}



/**
 * Set the position of this object
 * in the world. Adjusts the member model matrix.
 *
 * @param pos New position in world space
 */
void RenderObject::SetPosition(glm::vec3 pos)
{
    mPosition = pos;
}


/**
 * Set the rotation of this object, using glm/gtc's
 * angle/axis convention. Make sure your angle is in radians!
 * @param rads new angle in radians!
 * @param axis axis of rotation. make sure it's a valid axis!! (not the zero vector)
 */
void RenderObject::SetRotation(float rads, glm::vec3 axis)
{
    auto axisNorm = glm::normalize(axis);
    auto rotation = std::pair<float, glm::vec3>(rads, axisNorm);
    mRotation = rotation;
}


/**
 * Set the scale of the object.
 * 
 * This override gives the option of stretching
 * weirdly because it has a vector input.
 * 
 * @param scale New xyz scale of the object
 */
void RenderObject::SetScale(glm::vec3 scale)
{
    mScale = scale;
}


/**
 * Set the scale of the object.
 *
 * This override simply scales the object
 * in all dimensions evenly--it basically
 * shrinks/grows it to the provided scale
 *
 * @param scale New xyz scale of the object
 */
void RenderObject::SetScale(float scale)
{
    mScale = glm::vec3(scale);
}





