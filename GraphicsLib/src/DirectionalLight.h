/**
 * @file DirectionalLight.h
 * @author Elijah Gleckler
 *
 * Directional light source
 *
 *
 */

#ifndef LEARNING_OPENGL__DIRECTIONALLIGHT_H
#define LEARNING_OPENGL__DIRECTIONALLIGHT_H

#include "LightSource.h"

/**
 * Directional light source
 */
class DirectionalLight : public LightSource
{
private:

    /// The direction this source points *in world space*
    glm::vec3 mDirection;

public:

    /**
     * Constructor
     * @param direction Direction of the light source in world space
     * @param phongColors - attenuation coefficients of this light source
     * @param shaderProgram - this light source's associated shader program
     */
    DirectionalLight(   glm::vec3 direction,
                        std::shared_ptr<PhongColors> phongColors)
                        :
                        LightSource(phongColors), mDirection(direction)
                        {}

    /// Default constructor (disabled)
    DirectionalLight() = delete;

    /// Copy constructor (disabled)
    DirectionalLight(const DirectionalLight &) = delete;

    /// Assignment operator
    void operator=(const DirectionalLight &) = delete;


    // Must do this:
    void SetLightingUniforms(std::shared_ptr<Shader> shaders) override;



};

#endif //LEARNING_OPENGL__DIRECTIONALLIGHT_H
