/**
 * @file RenderObjectFactory.h
 * @author Elijah Gleckler
 *
 * Factory class for making render objects
 * out of filepaths to their assets.
 *
 * An optimization I think I implemented here
 * (well, I think it's an optimization....)
 * is the map between filename and Model/ShaderProgram.
 * I did this so that, instead of making new Model/
 * ShaderProgram objects, we can re-use the same ones and
 * save big on time when loading lots of things.
 *
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_RENDEROBJECTFACTORY_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_RENDEROBJECTFACTORY_H

#include <string>
#include <map>
#include <memory>
#include <nlohmann/json_fwd.hpp>

// for clarity... recommended by nlohmann
using json = nlohmann::json;

class ShaderProgram;
class Model;
class RenderObject;
/**
 * Factory class for making render objects
 * out of filepaths to their assets.
 */
class RenderObjectFactory
{
private:

    /// Path to the resource directory.
    /// It will be assumed that this directory is the one that
    /// contains directories named "shaders" and "models."
    /// DO NOT INLCUDE A '/' ON THE END!! It's ok...
    std::string mResourceDir;

    /// Map between  filenames and pointers for optimization
    std::map<std::string, std::shared_ptr<Model>> mModelsInUse;

    /// Map between shader filenames and pointers for optimization
    /// The string key will be a concatenation of the filenames  of
    /// the vertex and fragment shaders that make up the shader program
    /// represented by the ShaderProgram class. This will be a unique
    /// combination of strings... think about it...
    std::map<std::string, std::shared_ptr<ShaderProgram>> mShadersInUse;



public:

    /**
     * Constructor
     *
     * DO NOT PUT A '/' ON THE END OF THE FILEPATH!
     *
     * @param resourceDir   filepath to the "resources" directory that contains
     *                      other directories such as "shaders" and "models"
     */
    RenderObjectFactory(const std::string& resourceDir) : mResourceDir(resourceDir) {}

    /// Default constructor (disabled)
    RenderObjectFactory() = delete;

    /// Copy constructor (disabled)
    RenderObjectFactory(const RenderObjectFactory &) = delete;

    /// Assignment operator
    void operator=(const RenderObjectFactory &) = delete;

    // ****************************************************************

    RenderObject Create(const std::string& modelFile,
                        const std::string& vertShaderFile,
                        const std::string& fragShaderFile);

    RenderObject CreateFromJson(const nlohmann::json &configJson);

};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_RENDEROBJECTFACTORY_H
