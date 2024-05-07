///**
// * @file Texture2D.cpp
// * @author Elijah Gleckler
// */
//
//#include "Texture2D.h"
//
//#include <iostream>
//#include <glad/glad.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//
///**
// * Constructor
// * @param texName name of the texture for identification
// * @param imgPath filepath to the texture image
// * @param colorFormat the format of the color channels for the image we want to load
// * @param verticalFlip do we want to flip the texture vertically?
// * @param horizontalFlip do we want to flip the texture horizontally?
// */
//Texture2D::Texture2D(const std::string& texName, const char* imgPath,
//                     GLenum colorFormat, TextureType type, bool verticalFlip)
//                     : mTextureName(texName), mData(type)
//{
//
//    // Generate an OpenGL texture object (page 60)
//    glGenTextures(1, &mData.id);
//    glBindTexture(GL_TEXTURE_2D, mData.id);
//
//    // Now fill the struct that holds this class' data
//
//
//    // Specify the wrapping and filtering modes
//    // These are the defaults, but we'll provide a way to change them with some functions
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    // Load an image, getting its width, height, and number of color channels
//    int width, height, numChannels;
//    // Bytes array of the image:
//
//    stbi_set_flip_vertically_on_load(verticalFlip);
//    unsigned char* data = stbi_load(imgPath, &width, &height, &numChannels, 0);
//
//    // Don't mess with nullptrs...
//    if(data)
//    {
//        // And generate the texture
//        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout
//        << "********************************************************************************" << std::endl
//        << "ERROR IN TEXTURE \"" << mTextureName << "\"\nwhile loading image at: " << imgPath << std::endl
//        << "********************************************************************************" << std::endl;
//    }
//
//    // "After we’re done generating the texture and its corresponding mipmaps,
//    // it is good practice to free the image memory:"
//    stbi_image_free(data);
//
//    // Unbind the texture so OpenGL can do other stuff
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//
//}
//
//
//
///**
// * Binds the texture for use
// */
//void Texture2D::use() const
//{
//    glBindTexture(GL_TEXTURE_2D, mData.id);
//}
//
//
//
///**
// * Set the filter mode of the texture
// * @param mode new filter mode
// */
//void Texture2D::setFilterMode(GLenum mode)
//{
//    glBindTexture(GL_TEXTURE_2D, mData.id);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//
//
///**
// * Set the wrap mode of the texture
// * @param mode new wrap mode
// */
//void Texture2D::setWrapMode(GLenum mode)
//{
//    glBindTexture(GL_TEXTURE_2D, mData.id);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
