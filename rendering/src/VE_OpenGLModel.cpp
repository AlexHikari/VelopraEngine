#include "VE_OpenGLModel.h"
#include "VE_ITexture.h"
#include "VE_OpenGLMesh.h"
#include "VE_OpenGLRenderer.h"
#include "VE_OpenGLTexture.h"
#include "VE_pch.h"

namespace velopraEngine {
namespace render {

OpenGLModel::OpenGLModel(const std::string &path, OpenGLRenderer &renderer)
    : renderer(&renderer), transform(std::make_unique<OpenGLTransform>()) {
  LoadModel(path);
  VELOPRA_CORE_INFO("Loading model: {}", path);
}

void OpenGLModel::Draw() const {
  for (const auto &mesh : meshes) {
    mesh.Draw();
  }
}

void OpenGLModel::LoadModel(const std::string &path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals |
                aiProcess_JoinIdenticalVertices);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    VELOPRA_CORE_ERROR("Assimp error: {}", importer.GetErrorString());
    return;
  }
  directory = path.substr(0, path.find_last_of('/'));

  ProcessNode(scene->mRootNode, scene);
  VELOPRA_CORE_INFO("Model loaded");
}

void OpenGLModel::ProcessNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(std::move(ProcessMesh(mesh, scene)));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}

OpenGLMesh OpenGLModel::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    vertex.position = core::Vector3(
        mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

    if (mesh->HasNormals()) {
      vertex.normal = core::Vector3(
          mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
    }

    if (mesh->mTextureCoords[0]) {
      vertex.texCoords = core::Vector2(mesh->mTextureCoords[0][i].x,
                                       mesh->mTextureCoords[0][i].y);
    } else {
      vertex.texCoords = core::Vector2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  // Process materials
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<GLuint> diffuseMaps = LoadMaterialTextures(
        material, aiTextureType_DIFFUSE, "texture_diffuse");
    std::vector<GLuint> specularMaps = LoadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    // More texture types can be loaded if needed
  }

  return OpenGLMesh(std::move(vertices), std::move(indices));
}

std::vector<GLuint>
OpenGLModel::LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                  const std::string &typeName) {
  std::vector<GLuint> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);
    std::string filename = std::string(str.C_Str());
    filename = directory + '/' + filename;

    VELOPRA_CORE_INFO("Loading texture: {}", filename);

    std::shared_ptr<ITexture> texturePtr = renderer->LoadTexture(filename);
    auto openglTexture = std::dynamic_pointer_cast<OpenGLTexture>(texturePtr);
    if (openglTexture) {
      GLuint textureID = openglTexture->GetTextureId();
      textures.push_back(textureID);
    }
  }
  return textures;
}

void OpenGLModel::SetTransform(const ITransform &transform) {
  *this->transform = transform;
}

ITransform &OpenGLModel::GetTransform() { return *transform; }

} // namespace render
} // namespace velopraEngine