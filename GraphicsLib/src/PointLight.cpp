/**
 * @file PointLight.cpp
 * @author Elijah Gleckler
 */

#include "PointLight.h"
#include "ShaderProgram.h"


/**
 * Set the lighting uniforms in the provided shader program.
 * Relies heavily on a guarantee that the naming conventions
 * in all possible shader programs are consistent!
 *
 * The way point lights work in the shader is unique to
 * the other light types, so overriding is necessary.
 *
 * @param shaders Currently bound ShaderProgram program into which to insert uniforms
 */
void PointLight::SetLightingUniforms(ShaderProgram &shaders)
{
    // Grab these values from the parent class
    auto phongColors = GetPhongColors();
    auto attenCoeffs = mAttenuationCoefficients;

    std::string indexStr = "pointLights[" + std::to_string(mShaderIndex) + "]";

    // Set a slew of uniforms in the shaders:
    shaders.setVec3Uniform(indexStr + ".position", mPosition);
    shaders.setVec3Uniform(indexStr + ".ambient", phongColors.ambient);
    shaders.setVec3Uniform(indexStr + ".diffuse", phongColors.diffuse); // darkened
    shaders.setVec3Uniform(indexStr + ".specular", phongColors.specular);
    shaders.set1FUniform(indexStr + ".constant", attenCoeffs.constant);
    shaders.set1FUniform(indexStr + ".linear", attenCoeffs.linear);
    shaders.set1FUniform(indexStr + ".quadratic", attenCoeffs.quadratic);

}
