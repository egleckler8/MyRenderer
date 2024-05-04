/**
 * @file Camera.h
 * @author Elijah Gleckler
 *
 * Camera class that moves around in 3D space
 * depending on using input
 */

#ifndef LEARNING_OPENGL__CAMERA_H
#define LEARNING_OPENGL__CAMERA_H

#include <glm/glm.hpp>

class GLFWwindow;
/**
 * Crude input handler for GLFW window
 */
class Camera
{
private:

    /// Input window associated with the handler
    GLFWwindow* mWindow;

    /// Camera position in 3D world space
    glm::vec3 mPosition = glm::vec3(0.0f,0.0f,0.0f);

    /// Camera pitch in 3D world space IN DEGREES! (rotation around x-axis)
    double mPitch = 0.0;

    /// Camera yaw in 3D world space IN DEGREES! (roation around y-axis)
    double mYaw = 90.0;

    /// Camera target vector in world space (NOT direction to target!)
    glm::vec3 mTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);

    /// Normal vector for the direction the camera is looking in world space
    glm::vec3 mDirection = glm::vec3(0.0f, 0.0f, 0.0f);

    /// Up vector in camera space. So glm can do the Gram-Schmidt thingy in lookAt
    static constexpr glm::vec3 UpVec = glm::vec3(0.0f, 1.0f, 0.0f);

    /// Vector IN WORLD SPACE that designates the direction of the front of the camera
    glm::vec3 mFrontVec = glm::vec3(0.0f,0.0f,1.0f);

    /// Vector in camera space that points right
    glm::vec3 mRightVec = glm::normalize(glm::cross(mFrontVec, UpVec));

    /// store the time of the window to compute animation in seconds
    double mLastTime = 0;

    /// The move speed for when the user manually moves the camera
    float mMoveSpeed = 5.0f;

    /// Sensitivity of camera rotation
    float mSensitivity = 0.15f;

    /// The last position of the mouse cursor, for camera rotation
    glm::vec2 mLastCursorPos = glm::vec2(300, 400);

    /// Is the left button being held down?
    bool mLeftMouseButtonIsDown = false;


    static void StaticCursorCallback(GLFWwindow* window, double x, double y);
    void CursorCallback(GLFWwindow* window , double x, double y);
    static void StaticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void RegisterUser(GLFWwindow* window);




public:

    // Constructor
    Camera(GLFWwindow* window, glm::vec3 pos);

    /// Default constructor (disabled)
    Camera() = delete;

    /// Copy constructor (disabled)
    Camera(const Camera &) = delete;

    /// Assignment operator
    void operator=(const Camera &) = delete;

    /**
     * Get the position of the camera
     * @return the position of the camera
     */
    glm::vec3 GetPosition() const { return mPosition; }

    /**
     * Set the position of the camera.
     * @param pos New position of the camera
     */
    void SetPosition(glm::vec3 pos) { mPosition = pos; }


    /**
     * Set the camera's target position.
     * @param pos New target position of the camera
     */
    void SetTargetPos(glm::vec3 pos) { mTargetPos = pos; }


    /**
     * Set the move speed of the camera when user
     * input manually drives it.
     *
     * @param s New speed of the camera
     */
    void SetMoveSpeed(double s) { mMoveSpeed = s; }


    /**
     * Set the sensitivity of camera rotation.
     * 0.1 is the default
     *
     * @param s New sensitivity value
     */
    void SetSensitivity(double s) { mSensitivity = s; }


    void SetDirection(double pitch, double yaw);


    void Update();
    glm::mat4 GetViewMatrix();

};

#endif //LEARNING_OPENGL__CAMERA_H
