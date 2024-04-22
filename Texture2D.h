/**
 * @file Texture2D.h
 * @author Elijah Gleckler
 *
 * Class to encapsulate the functionality of loading
 * an image into a 2D texture for OpenGl, using stb_image.h
 *
 */

#ifndef LEARNING_OPENGL__TEXTURE2D_H
#define LEARNING_OPENGL__TEXTURE2D_H

#include <string>
#include <glad/glad.h>

/**
 * Class to encapsulate OpenGL 2D texture functionality
 */
class Texture2D
{
private:

    /// Name of the texture for identification
    std::string mTextureName;

    /// OpenGL ID of the texture
    unsigned int mTextureID;


public:

    // Constructor
    Texture2D(const std::string& texName, const char* imgPath,
              GLenum colorFormat,  bool verticalFlip);

    /// Default constructor (disabled)
    Texture2D() = delete;

    /// Copy constructor (disabled)
    Texture2D(const Texture2D &) = delete;

    /// Assignment operator
    void operator=(const Texture2D &) = delete;

    void use();
    void setWrapMode(GLenum mode);
    void setFilterMode(GLenum mode);


};

#endif //LEARNING_OPENGL__TEXTURE2D_H
