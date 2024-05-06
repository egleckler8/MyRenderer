/**
 * @file Scene.h
 * @author Elijah Gleckler
 *
 * Manages display of all visible entities
 * in the game, taking care to render them
 * all if instructoed
 *
 * A collection of GameObjects, lighting
 * sources, and a camera holder
 */

#ifndef LEARNING_OPENGL__SCENE_H
#define LEARNING_OPENGL__SCENE_H

#include <glm.hpp>
#include <vector>

class RenderData;
class LightSource;
class Camera;
/**
 * Manages all the visible entities in the game
 */
class Scene
{
private:

    /// Pointers to all the Rendering data
    std::vector<RenderData*> mEntities;

    /// Pointers to all the LightSources
    std::vector<LightSource*> mLights;

    /// Pointer to the camera object
    std::shared_ptr<Camera> mCamera;

public:

    /// Default constructor (disabled)
    Scene() = delete;

    /// Copy constructor (disabled)
    Scene(const Scene &) = delete;

    /// Assignment operator
    void operator=(const Scene &) = delete;

    // ****************************************************************

    /**
     * Add a physical entity to the scene
     * @param entity thing to add
     */
    void AddEntity(RenderData* entity) { mEntities.push_back(entity); }

    /**
     * Add a light source to the scene
     * @param lightSrc
     */
    void AddLightSource(LightSource* lightSrc) { mLights.push_back(lightSrc); }

    void RenderScene(glm::mat4 projMat) const;


};

#endif //LEARNING_OPENGL__SCENE_H
