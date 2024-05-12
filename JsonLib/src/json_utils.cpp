/**
 * @file json_utils.cpp
 * @author Elijah Gleckler
 */

#include "nlohmann/json.hpp"
#include "json_utils.h"

using json = nlohmann::json;

/**
 * Get a position/direction vector from json data.
 * Should be of this format:
 *
 *  {
 *      "x": <x component>,
 *      "y": <y component>,
 *      "z": <z component>
 *  }
 *
 * @param data Data of the vector
 * @return glm::vec3 of the data
 */
glm::vec3 VectorFromJson(const json& data)
{
    float x, y, z;
    x = data.at("x");
    y = data.at("y");
    z = data.at("z");
    return glm::vec3(x, y, z);
}


/**
 * Get an RGB color vector from json data.
 * Should be of this format:
 *
 *  {
 *      "r": <red component>,
 *      "g": <green ... >,
 *      "b": <blue ...>
 *  }
 *
 * @param data data of the color
 * @return glm::vec3 RGB color vector
 */
glm::vec3 ColorFromJson(const json& data)
{
    float r, g, b;
    r = data.at("r");
    g = data.at("g");
    b = data.at("b");
    return glm::vec3(r, g, b);
}


/**
 * Get a rotation angle/axis pair from json data.
 * Should be of this format:
 *
 *  {
 *      "angle": <angle in degrees>,
 *      "axis":
 *      {
 *          "x": <x component>,
 *          "y": <y component>,
 *          "z": <z component>
 *      }
 *  }
 *
 *  NOTE: I've decided that the input from the json
 *  files should be in degrees, since they are much
 *  easier to work with as a human! Therefore, this
 *  since glm works in radians, this function will
 *  be the point of conversion from degrees to rads.
 *
 * @param data data of the rotation config
 * @return angle/axis rotation pair
 */
std::pair<float, glm::vec3> RotationFromJson(const nlohmann::json& data)
{
    float angle = data.at("angle");
    angle = glm::radians(angle); // convert to radians!
    glm::vec3 axis = VectorFromJson(data.at("axis"));
    return std::pair<float, glm::vec3>(angle, axis);
}
