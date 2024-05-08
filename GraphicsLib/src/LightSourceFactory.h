/**
 * @file LightSourceFactory.h
 * @author Elijah Gleckler
 *
 * Factory for light source objects.
 *
 * Creates a light source object conveniently
 * from a json config file, rather than having to
 * specify out all the different colors and coeffs
 * and such by hand...
 *
 * Can create all types of the light sources! Will
 * read in the type from the json and create the
 * appropriate object.
 */

#ifndef LEARNING_OPENGL_GRAPHICSLIB_SRC_LIGHTSOURCEFACTORY_H
#define LEARNING_OPENGL_GRAPHICSLIB_SRC_LIGHTSOURCEFACTORY_H

#include <string>
#include <nlohmann/json_fwd.hpp>

class LightSource;
class PointLight;
class DirectionalLight;
/**
 * Factory for light source objects.
 */
class LightSourceFactory
{
private:

    std::unique_ptr<PointLight> CreatePointLight(const nlohmann::json& configJson);
    std::unique_ptr<DirectionalLight> CreateDirectionalLight(const nlohmann::json &configJson);
    // void CreateSpotLight(const nlohmann::json& configJson);



public:

    /// Constructor (default)
    LightSourceFactory() {}

    /// Copy constructor (disabled)
    LightSourceFactory(const LightSourceFactory &) = delete;

    /// Assignment operator
    void operator=(const LightSourceFactory &) = delete;

    // ****************************************************************

    std::unique_ptr<LightSource> CreateFromJson(const nlohmann::json& configJson);


};

#endif //LEARNING_OPENGL_GRAPHICSLIB_SRC_LIGHTSOURCEFACTORY_H
