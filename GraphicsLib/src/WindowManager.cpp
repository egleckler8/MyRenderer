/**
 * @file WindowManager.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "WindowManager.h"
#include "Scene.h"

/**
 * Constructor
 *
 * Initializes a GLFW window and GLAD for managing OpenGL
 * function pointers.
 *
 * Then, get the system ready for rendering
 * by setting up some things that won't change, like the
 * perspective matrix, and enable GL_DEPTH_TEST
 *
 * @param screenWidth width of created window
 * @param screenHeight height of create window
 */
WindowManager::WindowManager(int screenWidth, int screenHeight)
{
    //
    // Initialize the window
    //

    // Instantiate the GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // This must be here for macOS
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Next, we're required to create a window object
    // Intialize the mWindow member
    mWindow = glfwCreateWindow(screenWidth,screenHeight,"TODO", nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // return -1;
    }
    glfwMakeContextCurrent(mWindow);
    // Bind the window resize to it
    glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallback);

    // Initialize GLAD
    // "In the previous chapter we mentioned that GLAD manages function pointers
    // for OpenGL, so we want to initialize GLAD before we call any OpenGL function:"
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialized GLAD" << std::endl;
        // return -1;
    }



    //
    // Pre-rendering checklist:
    //


    // Set the viewport to the correct size
    int fbSizeX, fbSizeY;
    glfwGetFramebufferSize(mWindow, &fbSizeX, &fbSizeY);
    glViewport(0, 0, fbSizeX, fbSizeY);
    // Damn! It worked, nice. It was from here:
    // https://stackoverflow.com/questions/76541033/why-is-my-triangles-been-drawn-in-left-bottom-side-of-the-window


    // This is required to be called in only one place, as
    // far as I know now. So, I'll just stick it here until
    // I learn it should be anywhere else.
    glEnable(GL_DEPTH_TEST);

    // The perspective matrix will likely never change, so here it is:
    // It might need some touching up depending on the game, however.
    // That's a later problem... :)     (bad idea, Eli...)
    mProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);

}


/**
 * Callback for adjusting the framebuffer size so we
 * can resize the window
 * @param window This has to be here to fulfill the glfwSetFramebufferSizeCallback params...
 * @param width new window width
 * @param height new window height
 */
void WindowManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



/**
 * Tell this scene to render itself to the viewport.
 *
 * @param scene Scene object encapsulating necessary rendering
 *              data for all the game objects
 */
void WindowManager::DisplayScene(const Scene& scene)
{

    if(!glfwWindowShouldClose(mWindow))
    {

        // Set the background void
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell the scene to render itself with
        // the provided projection matrix.
        // I chose to pass the projection matrix as a parameter
        // and store it in this class in such a manner because
        // the projection matrix depends on the window aspect
        // ratio, so it felt natural to have that here. However,
        // it might be more natural to move it in the future.
        scene.RenderScene(mProjectionMatrix);

    }
    else
    {
        // Hmm... is this the best place for this code?
        std::cout << "GLFW terminated." << std::endl;
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

}