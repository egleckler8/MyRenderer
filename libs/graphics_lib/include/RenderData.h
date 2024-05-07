/**
 * @file RenderData.h
 * @author Elijah Gleckler
 *
 * All the data necessary to render a 3D
 * object.
 *
 * Model class includes textures,
 * RenderData also stores model matrix
 * and has functionality to adjust it, and
 * stores a pointer to the shader program.
 */

#ifndef LEARNING_OPENGL__RENDERDATA_H
#define LEARNING_OPENGL__RENDERDATA_H

#include <memory>
#include "glm.hpp"

class Model;
class Shader;
class LightSource;
/**
 * All the data necessary to render a 3d object
 */
class RenderData
{
private:

    /// Model of the object, including meshes & textures.
    std::shared_ptr<Model> mModel;

    /// Shader program this object will follow.
    std::shared_ptr<Shader> mShaders;

    /// Model matrix for this object. Make sure to adjust this
    /// before rendering to make sure your object is in the right
    /// place, has the right rotation, and is the right size!
    glm::mat4 mModelMatrix = glm::mat4(1.0f);

public:

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
    RenderData(std::shared_ptr<Model> model, std::shared_ptr<Shader> shaders)
                : mModel(model), mShaders(shaders) {}

    /// Default constructor (disabled)
    RenderData() = delete;

    /// Copy constructor (disabled)
    RenderData(const RenderData &) = delete;

    /// Assignment operator
    void operator=(const RenderData &) = delete;

    // ****************************************************************

    void Render(glm::mat4 viewMat, glm::mat4 projMat, std::vector<LightSource*>& lights) const;



};

#endif //LEARNING_OPENGL__RENDERDATA_H
