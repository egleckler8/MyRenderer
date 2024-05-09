/**
 * @file GameObject.h
 * @author Elijah Gleckler
 *
 * Base class for an object in the game.
 *
 * At the bare minimum, all game entities
 * should be able to be rendered and have
 * a position and rotation.
 *
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECT_H
#define LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECT_H

#include <memory>
#include <GraphicsLib/api.h>
#include <glm.hpp>

class RenderObject;
class GameObjectVisitor;
/**
 * Base class for an object in the game.
 */
class GameObject
{
private:

    /// Rendering data for this entity
    RenderObject* mRenderData = nullptr;

    /// Position of this object in world space, in METERS.
    glm::vec3 mPosition = glm::vec3(0.0f);

    /// Size of this object... think of it like a rectangular prism hitbox.
    /// IN METERS!
    /// *** The object's position is centered in the middle of this, for now ***
    glm::vec3 mHitbox = glm::vec3(1.0f);

    /// Rotation orientation of this object--angle/axis pair.
    /// This is the convention used by the GraphicsLib
    /// First member of pair is angle in radians
    /// Second member is a vector representing the axis of rotation
    std::pair<float, glm::vec3> mRotation =
        std::pair<float, glm::vec3>(0.0, glm::vec3(1.0f, 0.0f, 0.0f));

public:


    /**
     * Construcotr
     * @param renderData    Unique ptr to the render data. What I'd like to
     *                      communicate here by using a unique_ptr is that
     *                      this GameObject will be the new owner of the
     *                      RenderObject instance.
     * @param position      Position in world space of the object
     * @param hitbox        Rectangular prism hitbox of the object
     * @param rotation      Axis/angle pair of the 3D rotation
     */
    GameObject(std::unique_ptr<RenderObject> renderData,
               glm::vec3 position, glm::vec3 hitbox,
               std::pair<float, glm::vec3> rotation)
               :
               mPosition(position), mHitbox(hitbox), mRotation(rotation)
               {
                    // Unpack the unique_ptr and take the raw ptr
                    mRenderData = std::move(renderData).get();
                    // The unique_ptr is moved to the constructor and
                    // destroyed when it then falls out of scope.
               }

    /// Default constructor (disabled)
    GameObject() = delete;

    /// Copy constructor (disabled)
    GameObject(const GameObject &) = delete;

    /// Assignment operator
    void operator=(const GameObject &) = delete;

    // ****************************************************************

    void AcceptVisitor(GameObjectVisitor& visitor);

    // ****************************************************************

    virtual void SetPosition(glm::vec3 pos);
    void SetRotation(float rads, glm::vec3 axis);

    /**
     * Get a pointer to the light source. Make a copy of the member ptr
     *
     * Maybe I could make this more airtight (against nullptr) later...
     *
     * @return Pointer to this object's render data
     */
    RenderObject* GetRenderData() const { return mRenderData; }




};

#endif //LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECT_H
