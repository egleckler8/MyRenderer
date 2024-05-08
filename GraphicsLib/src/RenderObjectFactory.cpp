/**
 * @file RenderObjectFactory.cpp
 * @author Elijah Gleckler
 */

#include "RenderObjectFactory.h"

#include "RenderObject.h"
#include "Shader.h"
#include "Model.h"

/**
 * Create a brand-new render object from the provided assets.
 *
 * Will not reload models that have been already loaded,
 * due to the member map variables.
 *
 * @param modelFile         File for the created object's 3D model, like a .obj
 * @param vertShaderFile    Vertex shader file
 * @param fragShaderFile    Fragment shader file
 *
 * @return  New RenderObject, using above assets,
 *          initialized to default pos/rotation/scale
 */
RenderObject RenderObjectFactory::Create(const std::string& modelFile,
                                         const std::string& vertShaderFile,
                                         const std::string& fragShaderFile)
{

    // First, let's see if we've already loaded this model
    std::shared_ptr<Model> modelPtr;
    auto modelIt = mModelsInUse.find(modelFile);
    if (modelIt != mModelsInUse.end())
    {
        // It has already been loaded, so just make a copy
        // of that pointer to use!
        modelPtr = modelIt->second;
    }
    else
    {
        // It has not been loaded yet, so do it now.
        // The model class loads from path to object file
        modelPtr = std::make_shared<Model>(modelFile.c_str());

        // Remember to insert this to the map, now!
        std::pair<std::string, std::shared_ptr<Model>> p(modelFile, modelPtr);
        mModelsInUse.insert(p);
    }

    // Have we already loaded the shaders, too?
    std::shared_ptr<ShaderProgram> shaderPtr;
    // Remember, a ShaderProgram instance is a shader program
    // with multiple shader files, so let's just concatenate
    // the provided shader file names to represent a unique
    // order of shaders in a program
    auto programName = vertShaderFile + fragShaderFile;
    auto shaderIt = mShadersInUse.find(programName);
    if (shaderIt != mShadersInUse.end())
    {
        // These shaders have already been compiled, so
        // make a copy of that pointer to use!
        shaderPtr = shaderIt->second;
    }
    else
    {
        // They have not been compiled yet, so do it now
        // Remember to build the full shader paths!
        auto vertFilepath = mResourceDir + '/' + vertShaderFile;
        auto fragFilepath = mResourceDir + '/' + fragShaderFile;
        shaderPtr = std::make_shared<ShaderProgram>(programName,
                                                    vertFilepath.c_str(),
                                                    fragFilepath.c_str());

        // Remember to insert this to the map, now!
        std::pair<std::string, std::shared_ptr<ShaderProgram>> p(programName, shaderPtr);
        mShadersInUse.insert(p);
    }

    // Oh yeah...
    return RenderObject(modelPtr, shaderPtr);
}
