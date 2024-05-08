/**
 * @file GameObject.cpp
 * @author Elijah Gleckler
 */

#include "GameObject.h"

#include "GameObjectVisitor.h"









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

