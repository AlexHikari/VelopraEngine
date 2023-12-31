#ifndef VE_OPENGLMODEL_H
#define VE_OPENGLMODEL_H

#include "VE_IModel.h"
#include "VE_ITransform.h"
#include "VE_OpenGLTransform.h"
#include "VE_OpenGLMesh.h"
#include "VE_OpenGLRenderer.h"
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
  std::vector<std::unique_ptr<OpenGLMesh>> meshes;
  std::string directory;
  OpenGLRenderer *renderer;
  std::unique_ptr<ITransform> transform;

  void LoadModel(const std::string &path);
  void ProcessNode(aiNode *node, const aiScene *scene);
  std::unique_ptr<OpenGLMesh> ProcessMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<GLuint> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                           const std::string &typeName);
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGLMODEL_H
