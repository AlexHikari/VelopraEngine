#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "VE_Logger.h"

Model::Model(const std::string& path) {
	LoadModel(path);
}

void Model::Draw() const {
	for (const auto& mesh : meshes) {
		mesh.Draw();
	}
}

void Model::LoadModel(const std::string& path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		VELOPRA_CORE_ERROR("Assimp error: {}", importer.GetErrorString());
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
	// Process all the node's meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	// Then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	// ... Convert aiMesh to your Mesh structure
	// This involves reading the mesh's vertices, normals, texture coordinates, etc.
}