/**
 * @file GameObjectLoader.cpp
 * @author Elijah Gleckler
 */

#include <nlohmann/json.hpp>

#include "GameObjectLoader.h"

#include <JsonLib/api.h>

#include "GameObject.h"
#include "LightSrcObject.h"
#include "PlayerObject.h"



/**
 * Load a single base class game object from json data.
 * The json should be formatted as follows:
 *
 * NOTE: This is this "data" attribute of a json object
 *       whose "type" attribute read "game_object"
 *
 *  {
 *      "render_data":
 *      {
 *          "model_file": <filename of 3d model with parent dir>,
 *          "vertex_shader_file":<filename of vertex shader>,
 *          "fragment_shader_file":<filename of fragment shader>
 *      },
 *      "position": {"x": <x component>, "y": <y ... >, "z": <z ...> },
 *      "hitbox": {"x": <width>, "y": <height>, "z": <depth> },
 *      "rotation":
 *      {
 *          "angle": <angle in degrees>,
 *          "axis": {"x": <x component>, "y": <y ...> , "z": <z ...> }
 *      }
 *  }
 *
 * @param data Json data to load from
 * @return Initialized GameObject
 */
std::unique_ptr<GameObject>
    GameObjectLoader::LoadObject(const nlohmann::json &data)
{
    // Render data
    auto renderDataJson = data.at("render_data");
    auto renderData = mRenderObjectFactory.CreateFromJson(renderDataJson);

    // Position
    auto positionData = data.at("position");
    auto position = VectorFromJson(positionData);

    // Hitbox
    auto hitBoxData = data.at("hitbox");
    auto hitbox = VectorFromJson(hitBoxData);

    // Rotation
    auto rotationData = data.at("rotation");
    auto rotation = RotationFromJson(rotationData);

    return std::make_unique<GameObject>(std::move(renderData), position, hitbox, rotation);
}


/**
 * Load a single base class game object from json data.
 * The json should be formatted as follows:
 *
 * NOTE: This is this "data" attribute of a json object
 *       whose "type" attribute read "light_source_object"
 *
 *  {
 *      "render_data": <as above, for base GameObject>,
 *      "position": <as above, for base GameObject>,
 *      "hitbox": <as above, for base GameObject>,
 *      "rotation": <as above, for base GameObject>,
 *      "light_source":
 *      {
 *          "type": <"point", "directional", or "spot">,
 *          "data": <json object of data corresponding to type>
 *      }
 *  }
 *
 *  See GraphicsLib/src/LightSourceFactory.cpp, check the functions
 *  CreatePointLight, CreateDirectionalLight, etc. for the json
 *  format expected for each type of light source.
 *
 * @param data Json data to load from
 * @return Initialized LightSrcObject
 */
std::unique_ptr<LightSrcObject>
    GameObjectLoader::LoadLightSrcObject(const json &data)
{
    // I hate to copy all this, but it's not quite that easy to
    // use the function LoadObject itself... due to its return type

    // Render data
    auto renderDataJson = data.at("render_data");
    auto renderData = mRenderObjectFactory.CreateFromJson(renderDataJson);

    // Position
    auto positionData = data.at("position");
    auto position = VectorFromJson(positionData);

    // Hitbox
    auto hitBoxData = data.at("hitbox");
    auto hitbox = VectorFromJson(hitBoxData);

    // Rotation
    auto rotationData = data.at("rotation");
    auto rotation = RotationFromJson(rotationData);

    // The light source
    auto lightSrcData = data.at("light_source");
    auto lightSrcPtr = mLightSourceFactory.CreateFromJson(lightSrcData);

    // Moving the unique_ptr's to their parents
    return std::make_unique<LightSrcObject>(std::move(renderData), position,
                                            hitbox, rotation, std::move(lightSrcPtr));
}



/**
 * Takes a json object with key "game_objects" whose
 * value is a json array of GameObject configurations and
 * iteratively loads it into a vector of GameObjects.
 * Json data for all GameObjects should be formatted as
 * specified in the above documentation.
 *
 * The format of the json is expected as follows:
 *
 *  {
 *      "game_objects":
 *      [
 *          <game object as above>,
 *          <game object>,
 *          <game object>,
 *          ...
 *      ]
 *  }
 *
 *
 * @param data Json object to load
 * @return collection of all the loaded game objects
 */
std::vector<std::unique_ptr<GameObject>> GameObjectLoader::LoadObjects(const json &data)
{
    auto gameObjectsData = data.at("game_objects");

    // Fill 'er up...
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    // Loop over all the json objects in the array
    for (const json& gameObjectData : gameObjectsData)
    {
        // We'll store the created GameObject here:
        std::unique_ptr<GameObject> gameObject;

        // Deduce & create the appropriate object type
        auto objectType = gameObjectData.at("type");
        if (objectType == "game_object")
        {
            gameObject = LoadObject(gameObjectData.at("data"));
        }
        else if (objectType == "light_source_object")
        {
            gameObject = LoadLightSrcObject(gameObjectData.at("data"));
        }
        // else if (objectType == "player_object")
        // {
        //     TODO - implement PlayerObject...
        //     gameObject = LoadPlayerObject(gameObjectData);
        // }
        else
        {
            throw std::runtime_error("JSON ERROR: "
                                     "Invalid \"type\" value for game object!");
        }

        // Give the vector ownership of the object
        gameObjects.push_back(std::move(gameObject));

    }

    // Return the vector
    return gameObjects;
}
