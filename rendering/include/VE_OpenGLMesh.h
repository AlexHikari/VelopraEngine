#ifndef VE_OPENGLMESH_H
#define VE_OPENGLMESH_H

#include <GL/glew.h>
#include <vector>
#include "VE_IMesh.h"

namespace velopraEngine {
namespace render {

class OpenGLMesh : public IMesh{
public:
  OpenGLMesh(const std::vector<Vertex> &vertices,
             const std::vector<GLuint> &indices);
  ~OpenGLMesh();

  OpenGLMesh(OpenGLMesh &&other) noexcept;
  OpenGLMesh &operator=(OpenGLMesh &&) noexcept;

  OpenGLMesh(const OpenGLMesh &) = delete;
  OpenGLMesh &operator=(const OpenGLMesh &) = delete;

  void Draw() const override;

private:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  GLuint VAO, VBO, EBO;

  void SetupMesh();
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGLMESH_H