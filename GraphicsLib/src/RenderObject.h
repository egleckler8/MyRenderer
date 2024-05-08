/**
 * @file RenderObject.h
 * @author Elijah Gleckler
 *
 * All the data necessary to render a 3D
 * object.
 *
 * Model class includes textures,
 * RenderObject also stores model matrix
 * and has functionality to adjust it, and
 * stores a pointer to the shader program.
 *
 * There is no option to set the position or
 * scale of the object yet, so that should be
 * done manually, after intialization, for now.
 * All object are intially located at (0,0,0) and
 * have scale 1.0 by default.
 */

#ifndef LEARNING_OPENGL__RENDERDATA_H
#define LEARNING_OPENGL__RENDERDATA_H

#include <memory>
#include <glm.hpp>

class Model;
class ShaderProgram;
class LightSource;
/**
 * All the data necessary to render a 3d object
 */
class RenderObject
{
private:

    /// 3D odel of the object, including meshes & textures.
    std::shared_ptr<Model> mModel = nullptr;

    /// ShaderProgram program this object will follow.
    std::shared_ptr<ShaderProgram> mShaders = nullptr;

    /// Model matrix for this object. Make sure to adjust this
    /// before rendering to make sure your object is in the right
    /// place, has the right rotation, and is the right size!
    glm::mat4 mModelMatrix = glm::mat4(1.0f);

    /// Position in world space
    glm::vec3 mPosition = glm::vec3(0.0f);

    /// Rotation angle/axis pair of the object.
    /// I decided it would be good to enforce the angle/axis coupling
    /// ANGLE IN RADIANS! (you can use glm::radians()...)
    /// Would be nice if it were normalized... SetRotation() does that...
    std::pair<float, glm::vec3> mRotation =
            std::pair<float, glm::vec3>(0.0, glm::vec3(1.0f, 0.0f, 0.0f));

    /// Scale of the object in world space. Sizes the model up/down
    /// or stretches it all silly-like
    glm::vec3 mScale = glm::vec3(1.0f);

    void UpdateModelMatrix();

public:


    RenderObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaders);

    /// Default constructor (disabled)
    RenderObject() = delete;

    /// Copy constructor (disabled)
    RenderObject(const RenderObject &) = delete;

    /// Assignment operator
    void operator=(const RenderObject &) = delete;

    // ****************************************************************

    void Render(glm::mat4 viewMat, glm::mat4 projMat,
                std::vector<LightSource*>& lights);

    void SetPosition(glm::vec3 pos);
    void SetRotation(float rads, glm::vec3 axis);
    void SetScale(glm::vec3 scale);
    void SetScale(float scale);



};

#endif //LEARNING_OPENGL__RENDERDATA_H
