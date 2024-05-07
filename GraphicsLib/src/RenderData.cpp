/**
 * @file RenderData.cpp
 * @author Elijah Gleckler
 */

#include "RenderData.h"
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
RenderData::RenderData(std::shared_ptr<Model> model, std::shared_ptr<Shader> shaders)
    : mModel(model), mShaders(shaders)
{



    
}






/**
 * Set the shader uniforms corresponding to the transformation
 * matrices. Does not deal with lighting at all!
 *
 * @param viewMat view matrix used to render this model
 * @param projMat projection matrix used to render this model
 */
void RenderData::Render(glm::mat4 viewMat, glm::mat4 projMat, std::vector<LightSource*>& lights) const
{

    // Model-View matrix and Normal Matrix
    glm::mat4 modelViewMat = viewMat * mModelMatrix;
    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(modelViewMat)));

    // Set the transformation uniforms
    mShaders->use(); // will not re-bind, OpenGL optimizes this for us
    mShaders->setMat4Uniform(MODEL_MAT_UNIFORM_NAME, mModelMatrix);
    mShaders->setMat4Uniform(VIEW_MAT_UNIFORM_NAME, viewMat);
    mShaders->setMat4Uniform(PROJ_MAT_UNIFORM_NAME, projMat);
    mShaders->setMat4Uniform(NORMAL_MAT_UNIFORM_NAME, normalMat);

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

