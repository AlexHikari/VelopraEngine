#ifndef VELOPRA_MODEL_H
#define VELOPRA_MODEL_H

#include "Mesh.h"
#include <assimp/scene.h>
#include <vector>
#include <string>

class Model {
public:
	Model(const std::string& path);
	void Draw() const;

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	// Methods for loading materials and textures might also be necessary
};

#endif // VELOPRA_MODEL_H