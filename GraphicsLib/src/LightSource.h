/**
 * @file LightSource.h
 * @author Elijah Gleckler
 *
 * A simple light source using the Phong model
 *
 * Encapsulates lots of functionality... this can
 * be considered a "functionality class" that other objects
 * can have ownership of if they want to implement light
 * source properties.
 */

#ifndef LEARNING_OPENGL__LIGHTSOURCE_H
#define LEARNING_OPENGL__LIGHTSOURCE_H

#include "lighting_structs.h"

#include <memory>
#include <glm.hpp>

class ShaderProgram;
/**
 * A simple light source using the Phong model
 */
class LightSource
{
private:

    /**
     * These vectors are RGB color values for the contributions
     * of this light source, using the Phong lighting model,
     * to each fragment in the associated shader.
     */
    PhongColors mPhongColors;

public:

    /**
     * Constructor
     * @param phongColors Ambient, diffuse, and specular colors
     *                    for Phong lighting model.
     */
    LightSource(PhongColors phongColors) : mPhongColors(phongColors) {}
    
    /// Default constructor (disabled)
    LightSource() = delete;
    
    /// Copy constructor (disabled)
    LightSource(const LightSource &) = delete;
    
    /// Assignment operator
    void operator=(const LightSource &) = delete;

    /// Virtual destructor
    virtual ~LightSource() {}

    /// Sets the uniforms corresponding to this light source
    /// in the associated shader program.
    virtual void SetLightingUniforms(std::shared_ptr<ShaderProgram> shaders) = 0;


    // ****************************************************************
    //                     Getters & Setters
    // ****************************************************************

    /**
     * Get the Phong lighting colors for this light source
     * @return the Phong lighting colors for this light source
     */
    PhongColors& GetPhongColors() { return mPhongColors; }

    /**
     * Set the ambient color of this light source
     * @param ambientColor - of this light source
     */
    void SetAmbientColor(const glm::vec3 &ambientColor)
    {
        mPhongColors.ambient = ambientColor;
    }

    /**
     * Set the diffuse color of this light source
     * @param diffuseColor - of this light source
     */
    void SetDiffuseColor(const glm::vec3 &diffuseColor)
    {
        mPhongColors.diffuse = diffuseColor;
    }

    /**
     * Set the specular color of this light source
     * @param specularColor - of this light source
     */
    void SetSpecularColor(const glm::vec3 &specularColor)
    {
        mPhongColors.specular = specularColor;
    }

};

#endif //LEARNING_OPENGL__LIGHTSOURCE_H
