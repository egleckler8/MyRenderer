/**
 * @file graphics.h
 * @author Elijah Gleckler
 *
 * Header file with all the necessary includes
 * to use my rendering engine's API
 */

#ifndef LEARNING_OPENGL_LIBS_GRAPHICS_INCLUDE_GRAPHICS_H
#define LEARNING_OPENGL_LIBS_GRAPHICS_INCLUDE_GRAPHICS_H

// All necessary includes for the API:
#include "../src/WindowManager.h"
#include "../src/Scene.h"
#include "../src/RenderObject.h"
#include "../src/LightSource.h"
#include "../src/PointLight.h"
#include "../src/DirectionalLight.h"
// #include "../src/SpotLight.h" // not ready, yet...
#include "../src/Camera.h"
#include "../src/Model.h"
#include "../src/ShaderProgram.h"
#include "../src/RenderObjectFactory.h"
#include "../src/LightSourceFactory.h"
#include "../src/GBuffer.h"
#include "../src/Skybox.h"

// kind of a mess right now... might split it up later.
// just throwing a lot in here so i can keep it to one
// include in main.cpp.



#endif //LEARNING_OPENGL_LIBS_GRAPHICS_INCLUDE_GRAPHICS_H
