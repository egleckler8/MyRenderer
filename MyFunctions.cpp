/**
 * @file MyFunctions.cpp
 * @author Elijah Gleckler
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MyFunctions.h"




/**
 * Adjusts the OpenGL viewport
 * @param window pointer to the window we're using
 * @param width new width
 * @param height new height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}