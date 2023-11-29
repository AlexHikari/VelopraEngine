#ifndef VE_OPENGLMESH_H
#define VE_OPENGLMESH_H

#include <GL/glew.h>
#include "interfaces/VE_IMesh.h"
#include <vector>

namespace velopraEngine {
namespace render {

struct GLMVertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

class OpenGLMesh : public IMesh {
public:
  OpenGLMesh(const std::vector<GLMVertex> &vertices,
             const std::vector<GLuint> &indices);
  ~OpenGLMesh() override;

  OpenGLMesh(OpenGLMesh &&other) noexcept;
  OpenGLMesh &operator=(OpenGLMesh &&other) noexcept;

  OpenGLMesh(const OpenGLMesh &) = delete;
  OpenGLMesh &operator=(const OpenGLMesh &) = delete;

  void Draw() const override;

private:
  std::vector<GLMVertex> vertices;
  std::vector<GLuint> indices;

  GLuint VAO, VBO, EBO;

  void SetupMesh();
  void CleanUp();
  static void CheckOpenGLError(const std::string &operation);
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGLMESH_H
