/**
 * @file LightSrcObject.cpp
 * @author Elijah Gleckler
 */

#include "LightSrcObject.h"
#include "GameObjectVisitor.h"

/**
 * Also set the position of the
 * member light source!
 * @param pos New position
 */
void LightSrcObject::SetPosition(glm::vec3 pos)
{
    GameObject::SetPosition(pos);
    // mLightSource.SetPosition(pos);
    // TODO it should be a point light... or, better a MovableLight...
}



/**
 * Tell this LightSrcObject to accept a visitor
 * @param visitor visitor to accept
 */
void LightSrcObject::AcceptVisitor(GameObjectVisitor &visitor)
{
    visitor.VisitLightSrcObject(this);
}
