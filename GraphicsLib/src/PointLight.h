/**
 * @file PointLight.h
 * @author Elijah Gleckler
 *
 * Point light functionality
 * 
 * A light source represented by a single point
 * 
 * Light is cast from it radially and is attenuated
 * by distance. Uses Phong model, as its parent
 */

#ifndef LEARNING_OPENGL__POINTLIGHT_H
#define LEARNING_OPENGL__POINTLIGHT_H

#include "LightSource.h"
#include "lighting_structs.h"
/**
 * A light source represented by a single point
 */
class PointLight : public LightSource
{
private:

    /// Position of this light source IN WORLD SPACE
    glm::vec3 mPosition = glm::vec3(0.0f);
    // will be set after initializiation

    /// Attenuation coefficients
    AttenuationCoefficients mAttenuationCoefficients;
    
public:

    /**
     * Constructor
     * @param phongColors - colors attributes of this light source
     * @param attenCoeffs - attenuation coefficients of this light source
     * @param shaderProgram - this light source's associated shader program
     */
    PointLight( PhongColors phongColors,
                AttenuationCoefficients attenCoeffs)
                :
                LightSource(phongColors),
                mAttenuationCoefficients(attenCoeffs)
                {}
    
    /// Default constructor (disabled)
    PointLight() = delete;
    
    /// Copy constructor (disabled)
    PointLight(const PointLight &) = delete;
    
    /// Assignment operator
    void operator=(const PointLight &) = delete;

    // Must do this:
    virtual void SetLightingUniforms(std::shared_ptr<ShaderProgram> shaders) override;


    // ****************************************************************
    //                     Getters & Setters
    // ****************************************************************

    /**
     * Set the position of this light source
     * @param pos the position of this light source
     */
    void SetPosition(glm::vec3 pos) { mPosition = pos; }


    // Should I add setters for the AttenuationCoefficients struct values?
    
    

};

#endif //LEARNING_OPENGL__POINTLIGHT_H
