/**
 * @file Model.h
 * @author Elijah Gleckler
 *
 * A whole 3D model with multiple meshes.
 * Model loading functionality with Assimp.
 *
 * Check this video to see how to carefully
 * make your own things in blender, then use
 * them here:
 *
 * https://www.youtube.com/watch?v=4DQquG_o-Ac
 *
 * (from LearnOpenGL pg. 172)
 *
 */

#ifndef LEARNING_OPENGL__MODEL_H
#define LEARNING_OPENGL__MODEL_H

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"// "had to" do this, some weird error on the constructor

class ShaderProgram;
/**
 * A whole 3D model with multiple meshes
 */
class Model
{
private:

    /// All the meshes that are a part of this model
    std::vector<std::shared_ptr<Mesh>> mMeshes;

    /// Directory holding the assets so we can load textures
    std::string mFileDirectory;

    /// For optimization, so we don't reload extra textures
    std::vector<TextureData> mTexturesLoaded;

    void LoadModel(const std::string& fileDirectory);
    void ProcessNode(aiNode* node, const aiScene* scene);
    std::shared_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<TextureData> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);
    unsigned int TextureFromFile(const char* filepath, std::string fileDirectory);


public:

    /**
     * Constructor
     * @param filepath filepath to the model's object file
     */
    explicit Model(const char* filepath);

    /// Default constructor (disabled)
    Model() = delete;

    /// Copy constructor (disabled)
    Model(const Model &) = delete;

    /// Assignment operator
    void operator=(const Model &) = delete;

    // ****************************************************************

    void Draw(ShaderProgram &shaders);



};

#endif //LEARNING_OPENGL__MODEL_H
