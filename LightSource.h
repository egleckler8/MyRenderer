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
#include <glm/glm.hpp>

class Shader;
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
    std::shared_ptr<PhongColors> mPhongColors;
    // TODO should I make this a unique_ptr?

    /// The shader program this light source is associated with
    std::shared_ptr<Shader> mShaderProgram;
    // every light source should have a shader that it can
    // talk to and set the shader's uniforms

protected:

    // should I move mShaderProgram here??

public:

    // Constructor
    LightSource(std::shared_ptr<PhongColors> phongColors,
                std::shared_ptr<Shader> shaderProgram)
                :
                mPhongColors(phongColors),
                mShaderProgram(shaderProgram)
                {}
    
    /// Default constructor (disabled)
    LightSource() = delete;
    
    /// Copy constructor (disabled)
    LightSource(const LightSource &) = delete;
    
    /// Assignment operator
    void operator=(const LightSource &) = delete;

    /// Sets the uniforms corresponding to this light source
    /// in the associated shader program.
    /// TODO Can I think of a better name for this?? Something like "use..."
    virtual void SetUniforms() = 0;


    // ****************************************************************
    //                     Getters & Setters
    // ****************************************************************

    /**
     * Get the shader program associated with this light source
     * @return the shader program associated with this light source
     */
    std::shared_ptr<Shader> GetShaderProgram() const { return mShaderProgram; }

    /**
     * Get the Phong lighting colors for this light source
     * @return the Phong lighting colors for this light source
     */
    std::shared_ptr<PhongColors> GetPhongColors() const { return mPhongColors; }

    /**
     * Set the ambient color of this light source
     * @param ambientColor - of this light source
     */
    void SetAmbientColor(const glm::vec3 &ambientColor)
    {
        mPhongColors->ambient = ambientColor;
    }

    /**
     * Set the diffuse color of this light source
     * @param diffuseColor - of this light source
     */
    void SetDiffuseColor(const glm::vec3 &diffuseColor)
    {
        mPhongColors->diffuse = diffuseColor;
    }

    /**
     * Set the specular color of this light source
     * @param specularColor - of this light source
     */
    void SetSpecularColor(const glm::vec3 &specularColor)
    {
        mPhongColors->specular = specularColor;
    }

};

#endif //LEARNING_OPENGL__LIGHTSOURCE_H