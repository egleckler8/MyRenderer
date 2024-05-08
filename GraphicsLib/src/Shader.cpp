/**
 * @file ShaderProgram.cpp
 * @author Elijah Gleckler
 */

#include "Shader.h"

#include "glad/glad.h"
#include "gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * Constructor
 * @param vertexPath filepath to the vertex shader GLSL code
 * @param fragmentPath filepath to the fragment shader GLSL code
 */
ShaderProgram::ShaderProgram(string programName, const char* vertexPath, const char* fragmentPath) : mProgramName(programName)
{

    //
    // 1. First, get the shader source code from the paths
    //

    string vertexCode;
    string fragmentCode;
    ifstream vertexShaderFile;
    ifstream fragmentShaderFile;

    // make sure that ifstreams can throw exceptions, for error checking
    vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    // We'll read them in separately so we can better tell, when we
    // receive an error, which one of the files gave an error

    // first try the vertex shader
    try
    {
        // open the files
        vertexShaderFile.open(vertexPath);

        // We'll read them into string streams
        stringstream vertexShaderStream;
        // reading the buffer contents into streams
        vertexShaderStream << vertexShaderFile.rdbuf();

        // close the file handlers
        vertexShaderFile.close();

        // turn the string streams into strings
        vertexCode = vertexShaderStream.str();

    }
    catch (ifstream::failure e)
    {
        std::cout
        << "********************************************************************************" << std::endl
        << "ERROR IN PROGRAM \"" << mProgramName << "\"\nwhile loading vertex shader source from: \"" << vertexPath << "\""
        << "\nCOULD NOT READ VERTEX SHADER FILE INPUT" << std::endl
        << "********************************************************************************" << std::endl;
    }

    // now try the fragment shader
    try
    {
        // open the file
        fragmentShaderFile.open(fragmentPath);

        // We'll read  into a string stream
        stringstream fragmentShaderStream;
        // reading the buffer contents into streams
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // close the file handler
        fragmentShaderFile.close();

        // turn the string stream into a string
        fragmentCode = fragmentShaderStream.str();

    }
    catch (ifstream::failure e)
    {
        std::cout
        << "********************************************************************************" << std::endl
        << "ERROR IN PROGRAM \"" << mProgramName << "\"\nwhile loading fragment shader source from: \"" << fragmentPath << "\"" << std::endl
        << "COULD NOT READ FRAGMENT SHADER FILE INPUT" << std::endl
        << "********************************************************************************" << std::endl;
    }

    // Convert the shader code into c-style strings
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();


    //
    // 2. Now, compile the shaders (keeping track of errors)
    //

    // We'll keep track of this for later, if necessary...
    int success;
    char infoLog[512];

    // Compiling the vertex shader:
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout
        << "********************************************************************************" << std::endl
        << "ERROR IN PROGRAM \"" << mProgramName << "\"\nwhile compiling vertex shader source code at: \"" << vertexPath << "\""
        << "\nVERTEX SHADER COMPILATION FAILED\n\ninfoLog:" << std::endl
        << infoLog  << std::endl
        << "********************************************************************************" << std::endl;
    }



    // Compiling the fragment shader:
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout
        << "********************************************************************************" << std::endl
        << "ERROR IN PROGRAM \"" << mProgramName << "\"\nwhile compiling fragment shader source code at: \"" << fragmentPath << "\""
        << "\nFRAGMENT SHADER COMPILATION FAILED\n\ninfoLog:" << std::endl
        << infoLog  << std::endl
        << "********************************************************************************" << std::endl;
    }



    //
    // 3. Link the shaders into a program
    //

    mProgramID = glCreateProgram();
    glAttachShader(mProgramID, vertexShader);
    glAttachShader(mProgramID, fragmentShader);
    glLinkProgram(mProgramID);

    // Check for linking errors
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(mProgramID, 512, nullptr, infoLog);
        std::cout
        << "********************************************************************************" << std::endl
        << "ERROR IN PROGRAM \"" << mProgramName << "\":\nSHADER PROGRAM LINKING FAILED" << std::endl
        << "Could not link \n\"" << vertexPath << "\"\nand\n\"" << fragmentPath << "\"" << std::endl
        << "\ninfoLog:\n" << infoLog << std::endl
        << "********************************************************************************" << std::endl;
    }

    // Delete the shaders.
    // They are no longer necessary...
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}


/**
 * Use this shader program.
 * Binds this shader program to OpenGL
 */
void ShaderProgram::use()
{
    glUseProgram(mProgramID);
}



/**
 * Set a bool uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * @param uniformName the name of the uniform we want to set
 * @param val the new value to set it to
 */
void ShaderProgram::setBoolUniform(const std::string &uniformName, bool val) const
{
    glUniform1i(glGetUniformLocation(mProgramID, uniformName.c_str()), (int)val);
}



/**
 * Set an integer uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * @param uniformName the name of the uniform we want to set
 * @param val the new value to set it to
 */
void ShaderProgram::setIntUniform(const std::string &uniformName, int val) const
{
    glUniform1i(glGetUniformLocation(mProgramID, uniformName.c_str()), val);
}



/**
 * Set a float uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * @param uniformName the name of the uniform we want to set
 * @param val the new value to set it to
 */
void ShaderProgram::set1FUniform(const std::string &uniformName, float val) const
{
    glUniform1f(glGetUniformLocation(mProgramID, uniformName.c_str()), val);
}


/**
 * Set a three-element float array uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * You'd better not segfault it!
 *
 * @param uniformName the name of the uniform we want to set
 * @param ary (Pointer to first element of) three element array, new value
 */
void ShaderProgram::set3FUniform(const std::string& uniformName, float ary[])
{
    glUniform3f(glGetUniformLocation(mProgramID, uniformName.c_str()), ary[0], ary[1], ary[2]);
}



/**
 * Set a four-element float array uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * You'd better not segfault it!
 *
 * @param uniformName the name of the uniform we want to set
 * @param ary (Pointer to first element of) four element array, new value
 */
void ShaderProgram::set4FUniform(const string &uniformName, float ary[])
{
    glUniform4f(glGetUniformLocation(mProgramID, uniformName.c_str()), ary[0], ary[1], ary[2], ary[3]);
}



/**
 * Set a four-by-four float matrix uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * @param uniformName the name of the uniform we want to set
 * @param mat the transformation matrix we want to pass in
 */
void ShaderProgram::setMat4Uniform(const std::string& uniformName, glm::mat4 mat)
{
    unsigned int loc = glGetUniformLocation(mProgramID, uniformName.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));

}



/**
 * Set a three-by-three float matrix uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * @param uniformName the name of the uniform we want to set
 * @param mat the transformation matrix we want to pass in
 */
void ShaderProgram::setMat3Uniform(const std::string& uniformName, glm::mat3 mat)
{
    unsigned int loc = glGetUniformLocation(mProgramID, uniformName.c_str());
    glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));

}



/**
 * Set a vec3 uniform in the shader program.
 * Will search for the uniform in the program source code.
 *
 * @param uniformName the name of the uniform we want to set
 * @param mat the vec3 we want to pass in
 */
void ShaderProgram::setVec3Uniform(const std::string& uniformName, glm::vec3 vec)
{
    unsigned int loc = glGetUniformLocation(mProgramID, uniformName.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(vec));
}