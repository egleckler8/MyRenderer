/**
 * @file WindowManager.cpp
 * @author Elijah Gleckler
 */

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "WindowManager.h"
#include "Scene.h"
#include "Camera.h"

/**
 * Constructor
 *
 * Initializes a GLFW window and GLAD for managing OpenGL
 * function pointers.
 *
 * Then, get the system ready for rendering
 * by setting up some things that won't change, like the
 * perspective matrix
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
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(mWindow);
    // Bind the window resize to it
    glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallback);

    // Initialize GLAD
    // "In the previous chapter we mentioned that GLAD manages function pointers
    // for OpenGL, so we want to initialize GLAD before we call any OpenGL function:"
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialized GLAD.");
    }



    //
    // Pre-rendering checklist:
    //

    // Set the viewport to the correct size
//    int fbSizeX, fbSizeY;
//    glfwGetFramebufferSize(mWindow, &fbSizeX, &fbSizeY);
//    glViewport(0, 0, fbSizeX, fbSizeY);
    // Damn! It worked, nice. It was from here:
    // https://stackoverflow.com/questions/76541033/why-is-my-triangles-been-drawn-in-left-bottom-side-of-the-window

    // The perspective matrix will likely never change, so here it is:
    // It might need some touching up depending on the game, however.
    // That's a later problem... :)     (bad idea, Eli...)
    mProjectionMatrix = glm::perspective(glm::radians(45.0f),
                                         (float)screenWidth / screenHeight, 0.1f, 100.0f);

    // Initialize the camera with the window,
    // since it initialized fine
    mCamera = std::make_shared<Camera>(mWindow);

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
    // TODO - some way to adjust perspective matrix... would be kinda clean B)
//    mProjectionMatrix = glm::perspective(glm::radians(45.0f),
//                                         (float)width / height, 0.1f, 100.0f);

}



/**
 * Tell this scene to render itself to the viewport.
 *
 * @param scene Scene object encapsulating necessary rendering
 *              data for all the game objects
 */
void WindowManager::UpdateWindow()
{
    if(!glfwWindowShouldClose(mWindow))
    {
        // Double-buffering, baby
        glfwSwapBuffers(mWindow);
        // The end is the beginning--it's a cycle...

        glfwPollEvents();
        mCamera->Update();

        // Rendering commands?
        // ... no, somewhere else...
    }
    else
    {
        // Hmm... is this the best place for this code?
        glfwTerminate();
        std::cout << "GLFW terminated." << std::endl;
    }
}


/**
 * Query glfw and get the window size
 * @return (width, height) pair of window size
 */
std::pair<int, int> WindowManager::GetWindowSize()
{
    std::pair<int, int> size;
    glfwGetWindowSize(mWindow, &size.first, &size.second);
    return size;
}
