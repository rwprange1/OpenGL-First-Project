#pragma once

#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <filesystem> // Required for std::filesystem
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Model
{
public:

	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh>    meshes;
	std::string directory;


	bool gammaCorrection;

	Model(const char* path, bool f) {
		loadModel(path, f);
	}

	void Draw(Shader& s);
	void loadModel(std::string s, bool  f);

private:

	

	
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
};

