/**
 * @file Shader.h
 * @author Elijah Gleckler
 *
 * Class to encapsulate the functionality of a GLSL shader
 * for portability.
 *
 * Is capable of reading shader files from
 * disk, compiling and linking them, and checking for errors
 *
 */

#ifndef LEARNING_OPENGL__SHADER_H
#define LEARNING_OPENGL__SHADER_H

#include <string>
#include <glm/glm.hpp>

/**
 * Class to encapsualte the functionality of a GLSL shader
 */
class Shader
{
private:

    /// Human-readable name of the shader program for identification
    std::string mProgramName;

    /// ID of the shader program this is a part of, used by OpenGL
    unsigned int mProgramID;

public:


    // Constructor
    Shader(std::string programName, const char* vertexPath, const char* fragmentPath);

    /// Default constructor (disabled)
    Shader() = delete;

    /// Copy constructor (disabled)
    Shader(const Shader &) = delete;

    /// Assignment operator
    void operator=(const Shader &) = delete;


    /**
     * Get the id of the shader program this shader belongs to
     * @return id of the shader program this shader belongs to
     */
    unsigned int GetProgramID() const { return mProgramID; }


    void use();
    void setBoolUniform(const std::string& uniformName, bool val) const;
    void setIntUniform(const std::string& uniformName, int val) const;
    void set1FUniform(const std::string& uniformName, float val) const;
    void set3FUniform(const std::string& uniformName, float ary[]);
    void set4FUniform(const std::string& uniformName, float ary[]);
    void setMat4FUniform(const std::string& uniformName, glm::mat4 mat);





};

#endif //LEARNING_OPENGL__SHADER_H
