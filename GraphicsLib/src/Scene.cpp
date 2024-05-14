/**
 * @file Scene.cpp
 * @author Elijah Gleckler
 */

#include "Scene.h"

#include "PointLight.h"


/**
 * Make sure each point light knows its
 * index in the vector so it can set the
 * proper uniforms.
 *
 * We'll just do it linearly in the list, so that the
 * first item is shader index 0, etc.
 */
void Scene::UpdatePointLightIndices()
{
    for(int i = 0; i < mPointLights.size(); ++i)
    {
        auto light = mPointLights.at(i);
        light->SetShaderIndex(i);
    }
}




/**
 * Add a light source to the scene, making sure
 * it is aware of its index in the vector so it
 * can properly set its uniforms.
 *
 * @param lightSrc
 */
void Scene::AddPointLight(PointLight *lightSrc)
{
    mPointLights.push_back(lightSrc);
    UpdatePointLightIndices();
}
