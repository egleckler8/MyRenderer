/**
 * @file DirectionalLight.cpp
 * @author Elijah Gleckler
 */

#include "DirectionalLight.h"
#include "Shader.h"

/**
 * Set the uniforms in the associated shader program
 * with the light source parameters this object stores
 *
 * The way directional lights work in the shader is unique to
 * the other light types, so overriding is necessary.
 *
 * ONLY SUPPORTS ONE DIRECTIONAL LIGHT RIGHT NOW...
 */
void DirectionalLight::SetUniforms()
{
    // Grab these values from the parent class
    auto shaders = GetShaderProgram();
    auto phongColors = GetPhongColors();

    // Set a slew of uniforms in the shaders:
    shaders->setVec3Uniform("dirLight.direction", mDirection);
    shaders->setVec3Uniform("dirLight.ambient", phongColors->ambient);
    shaders->setVec3Uniform("dirLight.diffuse", phongColors->diffuse); // darkened
    shaders->setVec3Uniform("dirLight.specular", phongColors->specular);

}
