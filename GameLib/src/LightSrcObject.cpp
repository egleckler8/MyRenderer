/**
 * @file LightSrcObject.cpp
 * @author Elijah Gleckler
 */

#include <GraphicsLib/api.h>

#include "LightSrcObject.h"
#include "GameObjectVisitor.h"


/**
 * Constructor
 * @param renderData Data for object model
 * @param hitbox Hitbox
 * @param lightSrc Pointer to the light source
 */
LightSrcObject::LightSrcObject(std::unique_ptr<RenderObject> renderData,
                               glm::vec3 position,
                               glm::vec3 hitbox,
                               std::pair<float, glm::vec3> rotation,
                               std::unique_ptr<PointLight> lightSrc)
    :
    GameObject(std::move(renderData), position, hitbox, rotation)
{
    // Move ownership to this object
    mLightSource = std::move(lightSrc);

    // Make sure the light source is positioned correctly!
    mLightSource->SetPosition(position);


}





/**
 * Also set the position of the
 * member light source!
 * @param pos New position
 */
void LightSrcObject::SetPosition(glm::vec3 pos)
{
    GameObject::SetPosition(pos);
    mLightSource->SetPosition(pos);
}



/**
 * Tell this LightSrcObject to accept a visitor
 * @param visitor visitor to accept
 */
void LightSrcObject::AcceptVisitor(GameObjectVisitor &visitor)
{
    visitor.VisitLightSrcObject(this);
}
