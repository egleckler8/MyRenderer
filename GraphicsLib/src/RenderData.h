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
#include <glm.hpp>

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


    RenderData(std::shared_ptr<Model> model, std::shared_ptr<Shader> shaders);

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
