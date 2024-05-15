/**
 * @file DirectionalLight.cpp
 * @author Elijah Gleckler
 */

#include "DirectionalLight.h"
#include "ShaderProgram.h"

/**
 * Set the lighting uniforms in the provided shader program.
 * Relies heavily on a guarantee that the naming conventions
 * in all possible shader programs are consistent!
 *
 * The way directional lights work in the shader is unique to
 * the other light types, so overriding is necessary.
 *
 * G-BUFFER SHADERS ONLY SUPPORT ONE DIRECTIONAL LIGHT RIGHT NOW...
 *
 * @param shaders Currently bound ShaderProgram program into which to insert uniforms
 */
void DirectionalLight::SetLightingUniforms(ShaderProgram &shaders)
{
    // Grab these values from the parent class
    auto phongColors = GetPhongColors();

    // Set a slew of uniforms in the shaders:
    shaders.SetVec3Uniform("dirLight.direction", mDirection);
    shaders.SetVec3Uniform("dirLight.ambient", phongColors.ambient);
    shaders.SetVec3Uniform("dirLight.diffuse", phongColors.diffuse); // darkened
    shaders.SetVec3Uniform("dirLight.specular", phongColors.specular);

}
