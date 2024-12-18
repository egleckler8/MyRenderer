/**
 * @file RenderObjectFactory.cpp
 * @author Elijah Gleckler
 */

#include "RenderObjectFactory.h"

#include <nlohmann/json.hpp>

#include "RenderObject.h"
#include "ShaderProgram.h"
#include "Model.h"

/**
 * Create a brand-new render object from the provided assets.
 *
 * Will not reload models that have been already loaded,
 * due to the member map variables.
 *
 * @param modelFile         File for the created object's 3D model, like a .obj.
 *                          This path should be relative to the "models" folder
 *                          in the resources directory, e.g. if the filepath is:
 *                          "../resources/models/backpack/backpack.obj", only use
 *                          "backpack/backpack.obj" as an argument.
 * @param vertShaderFile    Vertex shader file
 * @param fragShaderFile    Fragment shader file
 *
 * @return  New RenderObject, using above assets,
 *          initialized to default pos/rotation/scale
 */
std::unique_ptr<RenderObject>
    RenderObjectFactory::Create(const std::string& modelDirectory,
                                const std::string& vertShaderFile,
                                const std::string& fragShaderFile)
{

    // First, let's see if we've already loaded this model
    std::shared_ptr<Model> modelPtr;
    auto modelIt = mModelsInUse.find(modelDirectory);
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
        auto modelFilepath = mResourceDir + "/models/" + modelDirectory;
        modelPtr = std::make_shared<Model>(modelFilepath.c_str());

        // Remember to insert this to the map, now!
        std::pair<std::string, std::shared_ptr<Model>> p(modelDirectory, modelPtr);
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
        auto vertFilepath = mResourceDir + "/shaders/" + vertShaderFile;
        auto fragFilepath = mResourceDir + "/shaders/" + fragShaderFile;
        shaderPtr = std::make_shared<ShaderProgram>(programName,
                                                    vertFilepath.c_str(),
                                                    fragFilepath.c_str());

        // Remember to insert this to the map, now!
        std::pair<std::string, std::shared_ptr<ShaderProgram>> p(programName, shaderPtr);
        mShadersInUse.insert(p);
    }

    // Oh yeah...
    return std::make_unique<RenderObject>(modelPtr, shaderPtr);
}



/**
 * Create a RenderObject from a nlohmann::json object
 * conforming to this exact format:
 *
 * {
 *     "model_directory": <directory containing .obj file>,
 *     "vertex_shader_file":<filename of vertex shader>,
 *     "fragment_shader_file":<filename of fragment shader>
 * }
 *
 *
 * NOTE: "model_directory" must have the same name as the .obj file it contains.
 * For example, if the model file you want to load is "lantern.obj," make sure
 * that it located in a directory called "lantern" in the "resources" folder for
 * the project. Also make sure that all the appropriate textures are located
 * in "resources/lantern!"
 *
 * All filenames should be relative to the implied
 * directory within the resources directory, e.g.
 * the vertex shader "v4.vert" is assumed to be at the
 * filepath "root/resources/shaders/v4.vert," and the
 * model "backpack/backpack.obj" is assumed to be located
 * at "root/resources/models/backpack/backpack.obj"
 *
 * @param configJson json object holding filepaths to assets
 *
 * @return New RenderObject, using above assets,
 *         initialized to default pos/rotation/scale
 */
std::unique_ptr<RenderObject>
    RenderObjectFactory::CreateFromJson(const json& configJson)
{
    // Grab the asset filepath data from the json
    std::string modelDir = configJson.at("model_directory");
    std::string vertShaderFile = configJson.at("vertex_shader_file");
    std::string fragShaderFile = configJson.at("fragment_shader_file");

    return Create(modelDir, vertShaderFile, fragShaderFile);
}
