/**
 * @file CameraManager.h
 * @author Elijah Gleckler
 *
 * TODO
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_CAMERAMANAGER_H
#define LEARNING_OPENGL_GAMELIB_SRC_CAMERAMANAGER_H

class CameraManager
{
private:

    // Pointer to the camera, obviously

    // Should have a pointer to the PlayerObject
    // for a two-way association

    // Should be tracking a particular game object


public:

    /// Default constructor (disabled)
    CameraManager() = delete;

    /// Copy constructor (disabled)
    CameraManager(const CameraManager &) = delete;

    /// Assignment operator
    void operator=(const CameraManager &) = delete;

    // ****************************************************************

    // Track object method with pointer to game object
    // to track.

};

#endif //LEARNING_OPENGL_GAMELIB_SRC_CAMERAMANAGER_H
