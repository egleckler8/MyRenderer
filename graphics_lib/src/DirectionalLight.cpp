/**
 * @file DirectionalLight.cpp
 * @author Elijah Gleckler
 */

#include "DirectionalLight.h"
#include "Shader.h"

/**
 * Set the lighting uniforms in the provided shader program.
 * Relies heavily on a guarantee that the naming conventions
 * in all possible shader programs are consistent!
 *
 * The way directional lights work in the shader is unique to
 * the other light types, so overriding is necessary.
 *
 * ALL SHADERS ONLY SUPPORT ONE DIRECTIONAL LIGHT RIGHT NOW...
 *
 * @param shaders Shader program into which to insert uniforms
 */
void DirectionalLight::SetLightingUniforms(std::shared_ptr<Shader> shaders)
{
    // Grab these values from the parent class
    auto phongColors = GetPhongColors();

    // Set a slew of uniforms in the shaders:
    shaders->setVec3Uniform("dirLight.direction", mDirection);
    shaders->setVec3Uniform("dirLight.ambient", phongColors->ambient);
    shaders->setVec3Uniform("dirLight.diffuse", phongColors->diffuse); // darkened
    shaders->setVec3Uniform("dirLight.specular", phongColors->specular);

}
