#ifndef VELOPRA_MODEL_H
#define VELOPRA_MODEL_H

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <unordered_map>

class OpenGLRenderer;

class Model {
public:
	Model(const std::string& path, OpenGLRenderer& renderer);
	void Draw() const;

private:
	std::vector<Mesh> meshes;
	std::string directory;
	OpenGLRenderer* renderer;

	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<GLuint> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};

#endif // VELOPRA_MODEL_H