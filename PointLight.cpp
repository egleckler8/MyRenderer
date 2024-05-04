/**
 * @file PointLight.cpp
 * @author Elijah Gleckler
 */

#include "PointLight.h"
#include "Shader.h"

/**
 * Set the uniforms in the associated shader program
 * with the light source paraemeters this object stores
 */
void PointLight::SetUniforms()
{
    // Grab these values from the parent class
    auto shaders = GetShaderProgram();
    auto phongColors = GetPhongColors();
    auto attenCoeffs = mAttenuationCoefficients;

    // Set a slew of uniforms in the shaders:
    shaders->setVec3Uniform("pointLights[0].position", mPosition);
    shaders->setVec3Uniform("pointLights[0].ambient", phongColors->ambient);
    shaders->setVec3Uniform("pointLights[0].diffuse", phongColors->diffuse); // darkened
    shaders->setVec3Uniform("pointLights[0].specular", phongColors->specular);
    shaders->set1FUniform("pointLights[0].constant", attenCoeffs->constant);
    shaders->set1FUniform("pointLights[0].linear", attenCoeffs->linear);
    shaders->set1FUniform("pointLights[0].quadratic", attenCoeffs->quadratic);

}
