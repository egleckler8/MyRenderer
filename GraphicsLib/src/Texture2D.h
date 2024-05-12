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

enum TextureType
{
    Diffuse,
    Specular,
    Roughness,
};

// TODO docs
struct TextureData
{
    unsigned int id;
    TextureType type;
    std::string filepath;

    TextureData() {} // ugh
    //TextureData(TextureType type) : type(type) {}

};

//
///**
// * Class to encapsulate OpenGL 2D texture functionality
// */
//class Texture2D
//{
//private:
//
//    /// Name of this texture, for debugging
//    const std::string& mTextureName;
//
//    /// The data related to this texute: OpenGL ID and texture type
//    TextureData mData;
//
//    /// Is this a specular or diffuse texture?
//    TextureType mType;
//
//
//public:
//
//    // Constructor
////    Texture2D(const std::string& texName, const char* imgPath,
////              GLenum colorFormat, TextureType type, bool verticalFlip);
//
//    /// Default constructor (disabled)
//    Texture2D() = delete;
//
//    /// Copy constructor (disabled)
//    Texture2D(const Texture2D &) = delete;
//
//    /// Assignment operator
//    void operator=(const Texture2D &) = delete;
//
//    void use() const;
////    void setWrapMode(GLenum mode);
////    void setFilterMode(GLenum mode);
//
//    // ****************************************************************
//
//    /**
//     * Get the GL data associated with this texture
//     * @return Texture truct holding the GL id and texture type
//     */
//    TextureData GetData() const { return mData; }
//
//
//};

#endif //LEARNING_OPENGL__TEXTURE2D_H
