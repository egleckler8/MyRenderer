/**
 * @file RenderObject.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <gtc/matrix_transform.hpp>

#include "RenderObject.h"
#include "Shader.h"
#include "Model.h"
#include "LightSource.h"

/// Maximum number of light sources each shader should
/// deal with at a time.
const unsigned int MAX_LIGHTS_PER_SHADER = 16;

const std::string MODEL_MAT_UNIFORM_NAME = "modelMat";  ///< Naming convention for model matrix in shaders
const std::string VIEW_MAT_UNIFORM_NAME = "viewMat"; ///< Naming convention for view matrix in shaders
const std::string PROJ_MAT_UNIFORM_NAME = "projMat"; ///< Naming convention for projection matrix in shaders
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
 * matrices. Does not deal with lighting at all!
 *
 * @param viewMat view matrix used to render this model
 * @param projMat projection matrix used to render this model
 */
void RenderObject::Render(glm::mat4 viewMat, glm::mat4 projMat,
                          std::vector<LightSource*>& lights)
{
    if (mModel != nullptr && mShaders != nullptr)
    {
        // Update the model matrix based on our current
        // position, rotation, and scale
        UpdateModelMatrix();

        // Model-View matrix and Normal Matrix
        glm::mat4 modelViewMat = viewMat * mModelMatrix;
        glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(modelViewMat)));

        // Set the transformation uniforms
        mShaders->use(); // will not re-bind, OpenGL optimizes this for us
        mShaders->setMat4Uniform(MODEL_MAT_UNIFORM_NAME, mModelMatrix);
        mShaders->setMat4Uniform(VIEW_MAT_UNIFORM_NAME, viewMat);
        mShaders->setMat4Uniform(PROJ_MAT_UNIFORM_NAME, projMat);
        mShaders->setMat3Uniform(NORMAL_MAT_UNIFORM_NAME, normalMat);

        // Set lighting uniforms
        // THIS WILL FAIL HORRIBLY IF THE SHADERS DON'T FOLLOW THE
        // EXPECTED NAMING CONVENTIONS!!!

        // We neither want to exceed the maximum number of lights
        // (which we've also specified in the shaders) nor do we
        // want to index out of bounds on the light sources vector
        for (   int i = 0;
                i < lights.size() && i < MAX_LIGHTS_PER_SHADER;
                ++i)
        {
            auto light = lights.at(i);
            light->SetLightingUniforms(mShaders);
        }

        // Binding textures & shaders and setting uniforms
        // all happen in this call!
        mModel->Render(mShaders);
    }
    else
    {
        std::cout
        << "Be careful! Cannot render an instance with unitialized assets.\n"
        << "(RenderObject.cpp line 102)"
        << std::endl;
    }

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





