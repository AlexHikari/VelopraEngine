#include "VE_pch.h"
#include "interfaces/VE_ITexture.h"
#include "opengl/VE_OpenGLTexture.h"
#include "opengl/3d/VE_OpenGLModel.h"
#include "opengl/3d/VE_OpenGLMesh.h"
#include "opengl/3d/VE_OpenGLRenderer.h"

namespace velopraEngine {
namespace render {

OpenGLModel::OpenGLModel(const std::string &path, OpenGLRenderer &renderer)
    : renderer(&renderer), transform(std::make_unique<OpenGLTransform>()) {
  LoadModel(path);
  VELOPRA_CORE_INFO("Loading model: {}", path);
}

void OpenGLModel::Draw() const {
  for (const auto &mesh : meshes) {
    mesh->Draw();
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
  VELOPRA_CORE_INFO("Processing node: {}", node->mName.C_Str());
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(std::move(ProcessMesh(mesh, scene)));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}

std::unique_ptr<OpenGLMesh> OpenGLModel::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  VELOPRA_CORE_INFO("Processing mesh: {}", mesh->mName.C_Str());
  std::vector<GLMVertex> vertices;
  std::vector<GLuint> indices;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    GLMVertex vertex;
    glm::vec3 vector;

    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;

    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }

    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = vec;
    } else {
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
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

  VELOPRA_CORE_INFO("Mesh processed with {} vertices and {} indices",
                    vertices.size(), indices.size());
  auto newMesh =
      std::make_unique<OpenGLMesh>(std::move(vertices), std::move(indices));

  return newMesh;
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