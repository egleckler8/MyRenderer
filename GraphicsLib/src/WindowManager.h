/**
 * @file WindowManager.h
 * @author Elijah Gleckler
 *
 * Super awesome rendering engine.
 *
 * Creates and handles GLFW window.
 *
 * GameObjects will call a RenderScene function with
 * a pointer to a WindowManager as an argument
 * which will then call WindowManager::RenderScene
 * passing its RenderObject to this class.
 *
 * Also has to keep track of the camera!
 */

#ifndef LEARNING_OPENGL__WINDOWMANAGER_H
#define LEARNING_OPENGL__WINDOWMANAGER_H

#include <memory>
#include <glm.hpp>


class GLFWwindow;
class Scene;
class Camera;
/**
 * Super awesome rendering engine
 */
class WindowManager
{
private:

    /// GLFW window object this engine will render to
    GLFWwindow* mWindow;

    /// The perspective matrix rarely changes and is dependent
    /// on screen aspect ratio, so we'll keep it in this class
    glm::mat4 mProjectionMatrix;

    /// Camera to view the window. Constructed here.
    std::shared_ptr<Camera> mCamera;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

public:

    // Constructor
    WindowManager(int screenWidth, int screenHeight);

    /// Default constructor (disabled)
    WindowManager() = delete;

    /// Copy constructor (disabled)
    WindowManager(const WindowManager &) = delete;

    /// Assignment operator
    void operator=(const WindowManager &) = delete;

    // ****************************************************************

    /**
     * Get a pointer to this window's camera
     * @return pointer to this window's camera
     */
    std::shared_ptr<Camera> GetCamera() const { return mCamera; }

    /**
     * Get the projection matrix
     * @return the project matrix
     */
    glm::mat4 GetProjectionMatrix() const { return mProjectionMatrix; }

    std::pair<int, int> GetWindowSize();

    // ****************************************************************

    void UpdateWindow();



};

#endif //LEARNING_OPENGL__WINDOWMANAGER_H
