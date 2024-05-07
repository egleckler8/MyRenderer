/**
 * @file Camera.cpp
 * @author Elijah Gleckler
 */

#include "Camera.h"
#include "GLFW/glfw3.h"
#include "gtc/matrix_transform.hpp"
#include <iostream>



/**
 * Constructor
 * @param window GLFWWindow this camera will "inhabit"
 * @param pos Initial position of the camera in world space
 */
Camera::Camera(GLFWwindow *window) : mWindow(window)
{
    // Set up the window with some configurations that will
    // make the camera work as we want it to

    // The mouse will be hidden!
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Register the mouse callback function with the GLFW window
    // And register this camera as the user of the window
    RegisterUser(window);

}

/**
 * Checks the input of the window updates the camera
 * position appropriately
 */
void Camera::Update()
{

    glfwPollEvents();

    // Change in time
    double currentTime = glfwGetTime();
    double dT = currentTime - mLastTime;
    // Adjust for animation
    mLastTime = currentTime;


    // Only if it's valid...
    if (mWindow)
    {

        // Close the window if escape key is pressed
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        //
        // Check the ASDW keys and adjust x-z pos properly
        //

        // WS is z in camera space (forward/backward)
        if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
            mPosition += (mMoveSpeed * (float)dT) * mFrontVec;
        else if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
            mPosition -= (mMoveSpeed * (float)dT) * mFrontVec;

        // AD is x in camera space (left/right)
        if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
            mPosition += (mMoveSpeed * (float)dT) * mRightVec;
        else if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
            mPosition -= (mMoveSpeed * (float)dT) * mRightVec;

        // Moving vertically would be nice...
        // World vertical, not camera vertical.
        if (glfwGetKey(mWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
            mPosition += (mMoveSpeed * (float)dT) * UpVec;
        else if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            mPosition -= (mMoveSpeed * (float)dT * UpVec);


        // Having yaw rotation on the keys would be nice...
        // This could use adjusted in the future... it's super gross lowkey
        if (glfwGetKey(mWindow, GLFW_KEY_Q) == GLFW_PRESS)
            SetDirection(mPitch, mYaw - (2 * M_PI * mMoveSpeed * dT));
        else if (glfwGetKey(mWindow, GLFW_KEY_E) == GLFW_PRESS)
            SetDirection(mPitch, mYaw + (2 * M_PI * mMoveSpeed * dT));


    }

    //std::cout << "Pos: (" << mPosition.x << ',' << mPosition.y << ',' << mPosition.z << ')' << std::endl;
    // std::cout << "Pitch: " << mPitch << " | Yaw: " << mYaw << std::endl;


}


/**
 * Get the view matrix for this camera.
 * Computed using glm::lookAt and members
 *
 * @return view matrix for this camera
 */
glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::lookAt(mPosition, mPosition + mFrontVec, UpVec);

    return viewMat;
}


/**
 * Static function gets the current camera instance that
 * is using the GLFW window and calls the CursorCallback
 * function on it.
 *
 * @param window GLFW window of the mouse
 * @param x current mouse position x
 * @param y current mouse position y
 *
 */
void Camera::StaticCursorCallback(GLFWwindow *window, double x, double y)
{
    auto camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (camera != nullptr)
    {
        camera->CursorCallback(window, x, y);
    }

}


/**
 *  Updates the camera pitch and yaw based on
 *  the change in cursor position
 *
 *  All below code copied from LearnOpenGL pg. 103,
 *  I only slightly modified it
 *
 * @param window GLFW window of the mouse
 * @param x current mouse position x
 * @param y current mouse position y
 *
 */
void Camera::CursorCallback(GLFWwindow *window, double x, double y)
{
    if (mLeftMouseButtonIsDown)
    {

        // Calculate the offsets
        float xOffset = x - mLastCursorPos.x;
        float yOffset = mLastCursorPos.y - y; // reversed: y ranges bottom to top
        mLastCursorPos.x = x;
        mLastCursorPos.y = y;
        xOffset *= mSensitivity;
        yOffset *= mSensitivity;

        // Adjust the pitch and yaw & adjust camera direction basis
        SetDirection(mPitch + yOffset, mYaw + xOffset);




    }

}



/**
 * Set the direction of the camera, changing the
 * changing the basis vectors of the camera directions
 *
 * @param pitch new pitch, degrees
 * @param yaw new yaw, degrees
 */
void Camera::SetDirection(double pitch, double yaw)
{
    // Set the members
    mYaw = yaw;
    mPitch = pitch;

    // Avoid Euler angle weirdness
    if(mPitch > 89.0f)
        mPitch = 89.0f;
    if(mPitch < -89.0f)
        mPitch = -89.0f;

    // Computer the direction we should be pointing!
    glm::vec3 direction;
    direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    direction.y = sin(glm::radians(mPitch));
    direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    // And adjust our basis vectors
    mFrontVec = glm::normalize(direction);
    mRightVec = glm::normalize(glm::cross(mFrontVec, UpVec));


}



/**
 * Registers this camera instance as the current user
 * of the GLFW window
 */
void Camera::RegisterUser(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, StaticCursorCallback);
    glfwSetMouseButtonCallback(window, StaticMouseButtonCallback);
}




/**
 * Static function gets the current camera instance that
 * is using the GLFW window and calls the MouseButtonCallback
 * function on it.
 *
 * @param window GLFW window of the mouse
 * @param window
 */
void Camera::StaticMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    auto camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (camera != nullptr)
    {
        camera->MouseButtonCallback(window, button, action, mods);
    }

}




/**
 * Mouse event handler
 *
 * @param window GLFW window
 * @param button mouse button that has been pressed
 * @param action action of the button (GLFW_PRESS or GLFW_RELEASE?)
 * @param mods ?
 */
void Camera::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        // We need to set the cursor pos, so that we don't glitch around
        // and that clicking anywhere on the screen allows us to rotate smoothly
        double newCursorX, newCursorY;
        glfwGetCursorPos(window, &newCursorX, &newCursorY);

        if (action == GLFW_PRESS)
        {
            mLeftMouseButtonIsDown = true;
            mLastCursorPos = glm::vec2(newCursorX, newCursorY);
        }
        else if (action == GLFW_RELEASE)
        {
            mLeftMouseButtonIsDown = false;
            mLastCursorPos = glm::vec2(newCursorX, newCursorY);
        }

    }

}





