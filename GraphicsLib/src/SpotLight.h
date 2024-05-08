/**
 * @file SpotLight.h
 * @author Elijah Gleckler
 *
 * Spotlight-style light source, like a player-held flashlight.
 *
 * Has everything that PointLight has, and more, so I
 * decided to make this an inheritance relationship and
 * then override the SetLightingUniforms function because
 * SpotLights work differently in the shaders.
 *
 * In a way, SpotLight sources are just modified
 * PointLight sources in that they behave differently in
 * the shaders, but look the same on paper (as an object...)
 *
 * TODO Rethink this... if there are multiple spotlights, how to handle?
 *
 *
 */

#ifndef LEARNING_OPENGL__SPOTLIGHT_H
#define LEARNING_OPENGL__SPOTLIGHT_H

#include "PointLight.h"

/**
 * Spotlight-style light source, like a player-held flashlight.
 */
class SpotLight //: public PointLight
{
private:

public:

};

#endif //LEARNING_OPENGL__SPOTLIGHT_H
