/**
 * @file GameObjectLoader.h
 * @author Elijah Gleckler
 *
 * Loads GameObjects from json, deducing
 * the base type via the json's format.
 *
 * This includes loading LightSource and
 * RenderData objects!
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECTLOADER_H
#define LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECTLOADER_H

#include <vector>
#include <nlohmann/json_fwd.hpp>

class GameObject;
class LightSrcObject;
class PlayerObject;
class RenderObjectFactory;
class LightSourceFactory;
/**
 * Loads GameObjects from json
 */
class GameObjectLoader
{
private:

    /// Reference to a RenderObject factory so we can
    /// store shaders & models in one place when we load
    RenderObjectFactory& mRenderObjectFactory;

    /// Reference to LightSource factory so we can build light
    /// sources (without constructing a new object each time)
    LightSourceFactory& mLightSourceFactory;

public:

    /**
     * Constructor
     * @param rendObjFact   Reference to a RenderObject factory that keeps
     *                      a registry of shaders & models for optimization
     */
    GameObjectLoader(RenderObjectFactory& rendObjFact,
                     LightSourceFactory& lightSrcFact)
                     :
                     mRenderObjectFactory(rendObjFact),
                     mLightSourceFactory(lightSrcFact) {}

    /// Default constructor (disabled)
    GameObjectLoader() = delete;

    /// Copy constructor (disabled)
    GameObjectLoader(const GameObjectLoader &) = delete;

    /// Assignment operator
    void operator=(const GameObjectLoader &) = delete;

    // ****************************************************************

    std::vector<GameObject*> LoadObjects(const nlohmann::json& data);
    GameObject* LoadObject(const nlohmann::json& data);
    LightSrcObject* LoadLightSrcObject(const nlohmann::json& data);
    // std::unique_ptr<PlayerObject> LoadPlayerObject(const nlohmann::json& data);
    // TODO ^^ player object...




};

#endif //LEARNING_OPENGL_GAMELIB_SRC_GAMEOBJECTLOADER_H
