/**
 * @file DirectionalLight.cpp
 * @author Elijah Gleckler
 */

#include "DirectionalLight.h"

/**
 * Set the uniforms in the associated shader program
 * with the light source parameters this object stores
 *
 * The way directional lights work in the shader is unique to
 * the other light types, so overriding is necessary.
 */
void DirectionalLight::SetUniforms()
{
    // TODO
}
