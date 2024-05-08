/**
 * @file lighting_structs.h
 * @author Elijah Gleckler
 *
 * Some useful structs to encapsulate some of the
 * repeated values that are used for different
 * light sources
 *
 * Also includes some json loading functionality
 * for these structs using the conventions of the
 * json_utils.h
 */

#ifndef LEARNING_OPENGL__LIGHTING_STRUCTS_H
#define LEARNING_OPENGL__LIGHTING_STRUCTS_H

#include <glm.hpp>

/**
 * Simple struct to package up the color
 * vectors in the Phong lighting model
 */
struct PhongColors
{

    /// The color of ambient light from this source in RGB
    glm::vec3 ambient = glm::vec3(0.0f);

    /// The color of diffuse light from this source in RGB
    glm::vec3 diffuse = glm::vec3(0.0f);

    /// The color of specular light from this source in RGB
    glm::vec3 specular = glm::vec3(0.0f);

};

/**
 * Encapsulates the constants for calculating
 * lighting attenuation. Some light sources have.
 *
 * Will be used in the equation:
 *
 * 1.0 / (constant + linear * distance + quadratic * distance * distance)
 *
 * in the fragment shaders to make sure light dims
 * a little bit the further away we get from some sources
 */
struct AttenuationCoefficients
{
    /// Constant coefficient (almost always 1.0)
    float constant;

    /// Linear coefficient
    float linear;

    /// Quadratic coefficient
    float quadratic;

};





#endif //LEARNING_OPENGL__LIGHTING_STRUCTS_H


