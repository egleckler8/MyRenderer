/**
 * @file json_utils.h
 * @author Elijah Gleckler
 *
 * Since this engine will use a set of naming conventions
 * for json objects in config files, like the consistent
 * format for colors and vectors, I'll define a utils header
 * with the utility functions in the .cpp file.
 */

#ifndef LEARNING_OPENGL_GAMELIB_SRC_JSON_UTILS_H
#define LEARNING_OPENGL_GAMELIB_SRC_JSON_UTILS_H

#include "nlohmann/json_fwd.hpp"
#include "glm.hpp"


glm::vec3 VectorFromJson(const nlohmann::json& data);
glm::vec3 ColorFromJson(const nlohmann::json& data);
std::pair<float, glm::vec3> RotationFromJson(const nlohmann::json& data);



#endif //LEARNING_OPENGL_GAMELIB_SRC_JSON_UTILS_H
