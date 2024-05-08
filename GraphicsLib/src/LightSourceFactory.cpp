/**
 * @file LightSourceFactory.cpp
 * @author Elijah Gleckler
 */

#include <nlohmann/json.hpp>
#include <glm.hpp>

#include "LightSourceFactory.h"

#include <JsonLib/api.h>

#include "LightSource.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "lighting_structs.h"


using json = nlohmann::json;

// Json loading functions are declared at the end of the
// file for readability's sake.
PhongColors PhongColorsFromJson(const json& data);
AttenuationCoefficients AttenCoeffsFromJson(const json& data);




/**
 * Create a point light object from json.
 * The json should be formatted exactly as follows:
 *
 *  {
 *      "phong_colors":
 *      {
 *          "ambient": { "r":<r>, "g":<g>, "b":<b> },
 *          "diffuse": { "r":<r>, "g":<g>, "b":<b> },
 *          "specular": { "r":<r>, "g":<g>, "b":<b> }
 *      },
 *      "attenuation_coefficients":
 *      {
 *          "constant": <constant coeff, probably 1.0...>,
 *          "linear": <linear coeff>,
 *          "quadratic": <quadratic coeff>
 *      }
 *  }
 *
 * ALL RGB VALUES SHOULD BE FLOATS FROM 0.0 TO 1.0!!
 *
 *
 * @param configJson json data to load phong colors & atten. coeffs.
 */
std::shared_ptr<PointLight>
    LightSourceFactory::CreatePointLight(const json &configJson)
{
    // Phong colors:
    auto phongData = configJson.at("phong_colors");
    PhongColors phongColors = PhongColorsFromJson(phongData);

    // Attenuation coeffiecients:
    auto attenCoeffData = configJson.at("attenuation_coefficients");
    AttenuationCoefficients attenCoeffs = AttenCoeffsFromJson(attenCoeffData);

    return std::make_shared<PointLight>(phongColors, attenCoeffs);
}



/**
 * Create a directional light object from json.
 * The json should be formatted exactly as follows:
 *
 * {
 *      "direction":
 *      {
 *          "x": <x component of direction vector>,
 *          "y": <y ... >,
 *          "z": <z ... >
 *      }
 *      "phong_colors":
 *      {
 *          "ambient": { "r":<r>, "g":<g>, "b":<b> },
 *          "diffuse": { "r":<r>, "g":<g>, "b":<b> },
 *          "specular": { "r":<r>, "g":<g>, "b":<b> }
 *      }
 *  }
 *
 * ALL RGB VALUES SHOULD BE FLOATS FROM 0.0 TO 1.0!!
 *
 * DIRECTION VECTOR DOES NOT HAVE TO BE NORMALIZED, BUT
 * IT WOULD SURE BE NICE...
 *
 * @param configJson json data to load phong colors & direction
 */
std::shared_ptr<DirectionalLight>
    LightSourceFactory::CreateDirectionalLight(const json &configJson)
{
    // Direction:
    auto directionData = configJson.at("direction");
    auto direction = VectorFromJson(directionData);

    // Phong colors:
    auto phongData = configJson.at("phong_colors");
    PhongColors phongColors = PhongColorsFromJson(phongData);

    return std::make_shared<DirectionalLight>(direction, phongColors);
}



/**
 * Create a light source from json. Deduces
 * the light source type from the json structure.
 * The json object for a light source should be formatted
 * exactly as follows:
 *
 *  {
 *      "type":<light source type: point, directional, spot...>,
 *      "data":<json object with that specific source's data>
 *  }
 *
 *
 * @param configJson json data to load the light source
 */
std::shared_ptr<LightSource>
    LightSourceFactory::CreateFromJson(const json &configJson)
{
    auto type = configJson.at("type");
    auto data = configJson.at("data");

    std::shared_ptr<LightSource> lightPtr = nullptr;

    // Create based on source type
    if (type == "point")
    {
        lightPtr = CreatePointLight(data);
    }
    else if (type == "directional")
    {
        lightPtr = CreateDirectionalLight(data);
    }


    // Some error handling in case someone messes
    // up the config files
    if (lightPtr == nullptr)
    {
        throw std::runtime_error("json config error. "
                                 "Attribute \"type\" of a light source was invalid.");
    }

    return lightPtr;
}


/**
 * Turns phong color json data into the struct.
 * Json must be formatted exactly as follows:
 *
 *  {
 *      "ambient": { "r":<r>, "g":<g>, "b":<b> },
 *      "diffuse": { "r":<r>, "g":<g>, "b":<b> },
 *      "specular": { "r":<r>, "g":<g>, "b":<b> }
 *  }
 *
 * @param data Json data for phong colors
 * @return Phong colors struct initialized with the data
 */
PhongColors PhongColorsFromJson(const json& data)
{
    // Phong colors:
    auto ambientData = data.at("ambient");
    auto diffuseData = data.at("diffuse");
    auto specularData = data.at("specular");

    auto ambientColor = ColorFromJson(ambientData);
    auto diffuseColor = ColorFromJson(diffuseData);
    auto specularColor = ColorFromJson(specularData);

    PhongColors phongColors;
    phongColors.ambient = ambientColor;
    phongColors.diffuse = diffuseColor;
    phongColors.specular = specularColor;

    return phongColors;
}



/**
 * Turns atten coeff json data into the struct.
 * Must be formatted exactly as follows:
 *
 *  {
 *      "constant": <constant coeff, probably 1.0...>,
 *      "linear": <linear coeff>,
 *      "quadratic": <quadratic coeff>
 *  }
 *
 * @param data json data
 * @return Atten coeff struct initialized with the data
 */
AttenuationCoefficients AttenCoeffsFromJson(const json& data)
{
    float c, l, q;
    c = data.at("constant");
    l = data.at("linear");
    q = data.at("quadratic");

    AttenuationCoefficients attenCoeffs;
    attenCoeffs.constant = c;
    attenCoeffs.linear = l;
    attenCoeffs.quadratic = q;

    return attenCoeffs;
}
