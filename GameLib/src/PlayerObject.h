/**
 * @file PlayerObject.h
 * @author Elijah Gleckler
 *
 * GameObject representing the player.
 *
 * Has a camera manager object that
 * handles the behavior of the camera in
 * relation to the player.
 *
 * Will I add a flashlight in the future???
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_PLAYEROBJECT_H
#define LEARNING_OPENGL_GAMELIB_SRC_PLAYEROBJECT_H

#include <memory>

#include "GameObject.h"

class CameraManager;
/**
 * GameObject representing the player.
 */
class PlayerObject : public GameObject
{
private:

    /// Camera man... Handles where the camera is
    /// in relation to the player.
    std::shared_ptr<CameraManager> mCameraMan = nullptr;


public:

    /**
     * Constructor
     * @param renderData Data for the character model
     * @param hitbox Player hitbox
     * @param cameraMan Camera manager pointer to track the player
     */
    PlayerObject(RenderObject* renderData,
                 glm::vec3 position, glm::vec3 hitbox,
                 std::pair<float, glm::vec3> rotation,
                 std::shared_ptr<CameraManager> cameraMan)
                 :
                 GameObject(renderData, position, hitbox, rotation),
                 mCameraMan(cameraMan) {}

    /// Default constructor (disabled)
    PlayerObject() = delete;

    /// Copy constructor (disabled)
    PlayerObject(const PlayerObject &) = delete;

    /// Assignment operator
    void operator=(const PlayerObject &) = delete;

    // ****************************************************************



};

#endif //LEARNING_OPENGL_GAMELIB_SRC_PLAYEROBJECT_H
