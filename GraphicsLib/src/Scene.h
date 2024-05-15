/**
 * @file Scene.h
 * @author Elijah Gleckler
 *
 * Manages display of all visible entities
 * in the game, taking care to render them
 * all if instructed.
 *
 * A collection of GameObjects and lighting sources
 *
 * TO BE CLEAR: A Scene object's data represents all the
 * physical game entities and lights a user of the API
 * wants the engine to consider for rendering.
 *
 * A typical
 * workflow would be to first load a bunch of game objects,
 * for a level, say. Then, when the game deems it aboute time to
 * render a set of objects, add them to a scene, and pass the
 * scene to Window::Display scene to start the rendering pipeline.
 *
 * It is not advisable to put all GameObjects in this class
 * from the get-go, unless the level is small! For example,
 * you probably wouldn't want to add the final boss of a level
 * to the scene right after you load the level, since the player
 * will start at the beginning of the level and there will be most
 * likely no need to consider rendering the final boss for a while.
 *
 */

#ifndef LEARNING_OPENGL__SCENE_H
#define LEARNING_OPENGL__SCENE_H

#include <glm.hpp>
#include <vector>

class RenderObject;
class PointLight;
class DirectionalLight;
class Camera;
/**
 * Manages all the visible entities in the game
 */
class Scene
{
private:

    /// Pointers to all the Rendering data
    std::vector<RenderObject*> mObjects;

    /// Pointers to all the movable LightSources
    std::vector<PointLight*> mPointLights;

    /// Pointer to a single directional light source
    /// It's my design choice that only one is allowed per scene
    DirectionalLight* mDirectionalLight;

    void UpdatePointLightIndices();

public:

    /// Default constructor
    Scene();

    /// Copy constructor (disabled)
    Scene(const Scene &) = delete;

    /// Assignment operator
    void operator=(const Scene &) = delete;

    // ****************************************************************

    /**
     * Get a reference to the list of render data for this scene
     * @return a reference to the list of render data for this scene
     */
    std::vector<RenderObject*>& GetRenderObjects() { return mObjects; }

    /**
     * Get a reference to the list of light sources in this scene
     * @return a reference to the list of light sources in this scene
     */
    std::vector<PointLight*>& GetPointLights() { return mPointLights; }

    /**
     * Get a pointer to the scene's single directional light
     * @return pointer to the sole directional light source
     */
    DirectionalLight* GetDirectionalLight() { return mDirectionalLight; }

    /**
     * Set the directional light of the scene.
     * Set it to nullptr to signify an absence of a directional light source
     * @param dirLight pointer to the new directional light source
     */
     void SetDirectionalLight(DirectionalLight* dirLight) { mDirectionalLight = dirLight; }

    /**
     * Add a physical entity to the scene
     * @param renderData thing to add
     */
    void AddRenderObject(RenderObject* renderData) { mObjects.push_back(renderData); }


    void AddPointLight(PointLight* lightSrc);

    // ****************************************************************





};

#endif //LEARNING_OPENGL__SCENE_H
