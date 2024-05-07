/**
 * @file Model.cpp
 * @author Elijah Gleckler
 */

#include "Model.h"

#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#include "Texture2D.h"



/**
 * Loads a model from it's filepath location
 *
 * Code copied from LearnOpenGL pg.165
 *
 * @param filepath Filepath of the model's file
 */
void Model::LoadModel(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
    // The pFlags argument is a set of post-processing flags that
    // assimp can run. Check pg. 165 of LearningOpenGL, there are
    // some nice ones, like "aiProcess_GenNormals" that might be
    // useful at some point in time later.

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cout
        << "****************************************************************" << std::endl
        << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl
        << "Occured when loading model from: " << filepath << std::endl
        << "****************************************************************" << std::endl;
        return;
    }
    mFileDirectory = filepath.substr(0, filepath.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);

}



/**
 * Process one node of the Assimp scene, then recursively
 * process its childen
 *
 * Code copied from LearnOpenGL pg. 166
 *
 * @param node Assimp node
 * @param scene Assimp scene object
 */
void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    // process all the node’s meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        mMeshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }

}




/**
 * Translate an aiMesh object into our Mesh object
 *
 * @param mesh Assimp aiMesh object
 * @param scene Assimo scene object
 * @return A Mesh object of our own making
 */
std::shared_ptr<Mesh> Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;

    // Get all the vertex data
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, ...
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // ... normals, ...
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        // ... and texture coordinates.
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);



        vertices.push_back(vertex);
    }


    // Get all the index data
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


    // Get all the material data
    if(mesh->mMaterialIndex >= 0)
    {
        // Get pointer to this particular material
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        // Load the material's diffuse maps
        std::vector<TextureData> diffuseMaps = LoadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE, TextureType::Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Load the material's specular maps
        std::vector<TextureData> specularMaps = LoadMaterialTextures(material,
                                                            aiTextureType_SPECULAR, TextureType::Specular);
        textures.insert(textures.end(), specularMaps.begin(),specularMaps.end());
    }

    // Make a shared pointer to share the love (no copy constructors  >:0  )
    return std::make_shared<Mesh>(vertices, indices, textures);
}



/**
 * Loads a texture from an Assimp material
 *
 * Code copied from LearnOpenGL pg.170
 *
 * @param mat pointer to Assimp material
 * @param type Assimp texture type enum
 * @param typeName Custom enum for texture types
 * @return vector of Texture data structs
 */
std::vector<TextureData> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType typeName)
{
    std::vector<TextureData> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < mTexturesLoaded.size(); j++)
        {
            if(std::strcmp(mTexturesLoaded[j].filepath.data(),
                           str.C_Str()) == 0)
            {
                textures.push_back(mTexturesLoaded[j]);
                skip = true;
                break;
            } }
        if(!skip)
        { // if texture hasn’t been loaded already, load it
            TextureData texture;
            texture.id = TextureFromFile(str.C_Str(), mFileDirectory);
            texture.type = typeName;
            texture.filepath = str.C_Str();
            textures.push_back(texture);
            mTexturesLoaded.push_back(texture); // add to loaded textures
        } }
    return textures;
}



/**
 * RenderScene all the Model's meshes
 * @param shader Shader program used to draw the meshes
 */
void Model::Render(std::shared_ptr<Shader> shader)
{
    for (unsigned int i = 0; i < mMeshes.size(); i++)
        mMeshes[i]->Render(shader);
}


/**
 * Taking the filepath to a texture image, generates the texture
 * and returns the OpenGL texture Id
 * @param filepath
 * @param fileDirectory
 * @return
 */
unsigned int Model::TextureFromFile(const char *filepath, std::string fileDirectory)
{

    // We'll need this...
    std::string fullFilepath = fileDirectory + '/' + std::string(filepath);

    // Generate an OpenGL texture object (page 60)
    unsigned int textureId;
    glGenTextures(1, &textureId);


    // Load an image, getting its width, height, and number of color channels
    int width, height, numChannels;
    // Bytes array of the image:

    // Shall we implement later?
    // Uh.... LearnOpenGL said they do this by default... idek why
    stbi_set_flip_vertically_on_load(true);

    // Load the image
    unsigned char* data = stbi_load(fullFilepath.c_str(), &width, &height, &numChannels, 0);

    // Don't mess with nullptrs...
    if(data)
    {
        // Find out what kind of colorformat this image is
        GLenum colorFormat;
        switch(numChannels)
        {
            case 1:
                colorFormat = GL_RED;
                break;

            case 3:
                colorFormat = GL_RGB;
                break;

            case 4:
                colorFormat = GL_RGBA;
                break;

        }


        // Bind and generate the texture
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Specify the wrapping and filtering modes
        // These are the defaults, but we'll provide a way to change them with some functions????
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }
    else
    {
        std::cout
            << "********************************************************************************" << std::endl
            << "ERROR IN TEXTURE \"" << filepath << "\"\nwhile loading image at: " << fullFilepath << std::endl
            << "********************************************************************************" << std::endl;
    }

    // "After we’re done generating the texture and its corresponding mipmaps,
    // it is good practice to free the image memory:"
    stbi_image_free(data);

    // Unbind the texture so OpenGL can do other stuff
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;

}
