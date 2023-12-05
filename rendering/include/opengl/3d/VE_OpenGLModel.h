#ifndef VE_OPENGLMODEL_H
#define VE_OPENGLMODEL_H

#include "interfaces/VE_IModel.h"
#include "interfaces/VE_ITransform.h"
#include "opengl/VE_OpenGLTransform.h"
#include "opengl/3d/VE_OpenGLMesh.h"
#include "opengl/3d/VE_OpenGLRenderer.h"
#include <string>
#include <vector>
#include <memory>

namespace velopraEngine {
namespace render {

class OpenGLModel : public IModel {
public:
  OpenGLModel(const std::string &path, OpenGLRenderer &renderer);
  ~OpenGLModel() override = default;

  void Draw() const override;
  void SetTransform(const ITransform &transform) override;
  ITransform &GetTransform() override;

private:
  std::vector<std::unique_ptr<OpenGLMesh>> m_meshes;
  std::string m_directory;
  OpenGLRenderer *m_renderer;
  std::unique_ptr<ITransform> m_transform;

  void LoadModel(const std::string &path);
  void ProcessNode(aiNode *node, const aiScene *scene);
  std::unique_ptr<OpenGLMesh> ProcessMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<GLuint> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                           const std::string &typeName);
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGLMODEL_H
