/**
 * @file ShaderProgram.h
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
#include <glm.hpp>

/**
 * Class to encapsulate the functionality of a GLSL shader
 */
class ShaderProgram
{
private:

    /// Human-readable name of the shader program for identification
    std::string mProgramName;

    /// ID of the shader program this is a part of, used by OpenGL
    unsigned int mProgramID;

    // Helper functions:
    unsigned int getUniformLoc(const std::string& uniformName);

public:


    // Constructor
    ShaderProgram(std::string programName, const char* vertexPath, const char* fragmentPath);

    /// Default constructor (disabled)
    ShaderProgram() = delete;

    /// Copy constructor (disabled)
    ShaderProgram(const ShaderProgram &) = delete;

    /// Assignment operator
    void operator=(const ShaderProgram &) = delete;

    void use();
    void setBoolUniform(const std::string& uniformName, bool val) const;
    void setIntUniform(const std::string& uniformName, int val) const;
    void set1FUniform(const std::string& uniformName, float val) const;
    void set3FUniform(const std::string& uniformName, float ary[]);
    void set4FUniform(const std::string& uniformName, float ary[]);
    void setMat4Uniform(const std::string& uniformName, glm::mat4 mat);
    void setVec3Uniform(const std::string& uniformName, glm::vec3 vec);
    void setMat3Uniform(const std::string& uniformName, glm::mat3 mat);





};

#endif //LEARNING_OPENGL__SHADER_H
