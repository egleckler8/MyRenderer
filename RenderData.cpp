/**
 * @file RenderData.cpp
 * @author Elijah Gleckler
 */

#include "RenderData.h"
#include "Shader.h"
#include "Model.h"

const std::string MODEL_MAT_UNIFORM_NAME = "modelMat";  ///< Naming convention for model matrix in shaders
const std::string VIEW_MAT_UNIFORM_NAME = "viewMat"; ///< Naming convention for view matrix in shaders
const std::string PROJ_MAT_UNIFORM_NAME = "projMat"; ///< Naming convention for projection matrix in shaders
const std::string NORMAL_MAT_UNIFORM_NAME = "normalMat"; ///< Naming convention for normal matrix in shaders


/**
 * RenderScene the object represented by this data
 *
 * @param viewMat view matrix used to render this model
 * @param projMat projection matrix used to render this model
 */
void RenderData::Render(glm::mat4 viewMat, glm::mat4 projMat) const
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

    // Binding textures & shaders and setting uniforms
    // all happen in this call!
    mModel->Render(mShaders);
}
