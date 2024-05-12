/**
 * @file GameObject.cpp
 * @author Elijah Gleckler
 */

#include "GameObject.h"

#include "GameObjectVisitor.h"



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
GameObject::GameObject(std::unique_ptr<RenderObject> renderData,
                       glm::vec3 position,
                       glm::vec3 hitbox,
                       std::pair<float, glm::vec3> rotation) :
                       mPosition(position), mHitbox(hitbox),
                       mRotation(rotation)
{
    // Move ownership of the RenderObject here.
    mRenderData = std::move(renderData);
    // Make sure to set the render data's position!
    mRenderData->SetPosition(mPosition);
    // and orientation...
    mRenderData->SetRotation(mRotation.first, mRotation.second);

    // Initialize a default behavior (does nothing on Update)
    mBehavior = std::make_unique<Behavior>(this);

}




/**
 * Set the position of this object, also
 * adjusting the position of the render data
 * @param pos New position in 3D space
 */
void GameObject::SetPosition(glm::vec3 pos)
{
    mPosition = pos;
    mRenderData->SetPosition(mPosition);
}



/**
 * Set the rotation of this object, also
 * adjusting the rotation of the render data
 * @param rads Angle in radians
 * @param axis Axis of rotation
 */
void GameObject::SetRotation(float rads, glm::vec3 axis)
{
    mRotation = std::pair<float, glm::vec3>(rads, axis);
    mRenderData->SetRotation(rads, axis);
}


/**
 * Accept a GameObject visitor. In this concrete base class,
 * simply call the base VisitGameObject method.
 *
 * @param visitor GameObject visitor to accept
 */
void GameObject::AcceptVisitor(GameObjectVisitor &visitor)
{
    visitor.VisitGameObject(this);
}


/**
 * Set the behavior of this object and establish the
 * two-way association between Behavior and exhibitor.
 *
 * @param behavior New behavior
 */
void GameObject::SetBehavior(std::unique_ptr<Behavior> behavior)
{
    mBehavior = std::move(behavior);
    mBehavior->SetExhibitor(this);
}



/**
 * Update this object based on its Behavior.
 * @param dt
 */
void GameObject::Update(double dt)
{
    // No nullptr access... make sure to set the behavior!
    // Actually... maybe I should make this an error...
    if (mBehavior != nullptr)
    {
        mBehavior->Update(dt);
    }

}
