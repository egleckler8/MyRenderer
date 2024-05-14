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
 * @param shaders ShaderProgram program into which to insert uniforms
 */
void PointLight::SetLightingUniforms(std::shared_ptr<ShaderProgram> shaders)
{
    // Grab these values from the parent class
    auto phongColors = GetPhongColors();
    auto attenCoeffs = mAttenuationCoefficients;

    // Set a slew of uniforms in the shaders:
    shaders->use();
    shaders->setVec3Uniform("pointLights[0].position", mPosition);
    shaders->setVec3Uniform("pointLights[0].ambient", phongColors.ambient);
    shaders->setVec3Uniform("pointLights[0].diffuse", phongColors.diffuse); // darkened
    shaders->setVec3Uniform("pointLights[0].specular", phongColors.specular);
    shaders->set1FUniform("pointLights[0].constant", attenCoeffs.constant);
    shaders->set1FUniform("pointLights[0].linear", attenCoeffs.linear);
    shaders->set1FUniform("pointLights[0].quadratic", attenCoeffs.quadratic);

}
