/**
 * @file SceneBuilderVisitor.cpp
 * @author Elijah Gleckler
 */

#include "SceneBuilderVisitor.h"

#include "GameObject.h"
#include "LightSrcObject.h"
#include "PlayerObject.h"

/**
 * Visit a general gameObject
 *
 * Adds the object's render data to the scene
 *
 * @param gameObject GameObject to visit
 */
void SceneBuilderVisitor::VisitGameObject(GameObject *gameObject)
{
    mScene->AddRenderObject(gameObject->GetRenderData());
}



/**
 * Visit a Game object with a light source
 *
 * Adds the object's render data as well as
 * its light source to the scene.
 *
 * @param lightSrcObject LightSrcObject to visit
 */
void SceneBuilderVisitor::VisitLightSrcObject(LightSrcObject *lightSrcObject)
{
    VisitGameObject(lightSrcObject);
    mScene->AddLightSource(lightSrcObject->GetLightSource());
}



/**
 * Visit a Player object with a CameraManager
 *
 * Adds the object's render data to the scene,
 * as well as...? TODO
 *
 * @param playerObject PlayerObject to visitor
 */
void SceneBuilderVisitor::VisitPlayerObject(PlayerObject *playerObject)
{
    VisitGameObject(playerObject);
    // anything else with the camera?
}

