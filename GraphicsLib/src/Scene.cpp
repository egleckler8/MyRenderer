/**
 * @file Scene.cpp
 * @author Elijah Gleckler
 */

#include "Scene.h"

#include "RenderObject.h"
#include "Camera.h"
#include "Model.h"


/**
 * Render all the objects and lighting
 * with OpenGL.
 *
 * @param projMat Projection matrix from the window
 * @param viewMat View matrix from the camera
 */
void Scene::RenderScene(glm::mat4 viewMat, glm::mat4 projMat) const
{
    /*
     problem: we have a list of light sources
     and a list of rendering data with shaders

     how do we know how to pair up the light sources
     and the shaders?

     currently, LightSource is storing a pointer to
     a singular shader program. that must change, since
     each object might have its own shader program.

     so, we need to devise some algo to make sure
     light sources get rendered in a logical manner.
     i.e. we need to set the uniforms in each of the RenderObject's
     shaders in a way that makes the final, lighted,
     rendered object look normal.

     this can lead to some optimizations... we can cleverly
     choose which light sources we want to apply to which
     shaders. this could lead to some optimizations around
     distance--if a light source is significantly far from
     an object, we don't have to use that light source in
     that objects shader uniforms.

     */

    // We can have fun optimizing this...
    // we'll only add certain lights to this list
    // We'll fully free to only add certain lights
    // to the list. I'll have to make sure it's a real bottleneck
    // before doing any sorting, though.
    auto lightsAffectingThisObject = mLights;

    // Crude...
    for (auto entity : mObjects)
    {
        entity->Render(viewMat, projMat, lightsAffectingThisObject);
    }
    // Now we should be good??


}
