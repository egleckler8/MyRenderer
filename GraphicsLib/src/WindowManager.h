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
 * passing its RenderData to this class.
 *
 * Also has to keep track of the camera!
 */

#ifndef LEARNING_OPENGL__WINDOWMANAGER_H
#define LEARNING_OPENGL__WINDOWMANAGER_H


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

    /// Camera to view the window
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

    void DisplayScene(const Scene &scene);

    /**
     * Get the GLFW window managed by this class
     * @return pointer to a GLFW window
     */
    GLFWwindow* GetWindow() const { return mWindow; }



};

#endif //LEARNING_OPENGL__WINDOWMANAGER_H
