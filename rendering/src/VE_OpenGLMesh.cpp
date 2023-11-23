#include "VE_OpenGLMesh.h"
#include "VE_pch.h"

namespace velopraEngine {
namespace render {

OpenGLMesh::OpenGLMesh(const std::vector<Vertex> &vertices,
           const std::vector<GLuint> &indices)
    : vertices(vertices), indices(indices) {
  SetupMesh();
}

// Move constructor
OpenGLMesh::OpenGLMesh(OpenGLMesh &&other) noexcept
    : VAO(other.VAO), VBO(other.VBO), EBO(other.EBO),
      vertices(std::move(other.vertices)), indices(std::move(other.indices)) {
  other.VAO = 0;
  other.VBO = 0;
  other.EBO = 0;
}

// Move assignment operator
OpenGLMesh &OpenGLMesh::operator=(OpenGLMesh &&other) noexcept {
  if (this != &other) {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;
    vertices = std::move(other.vertices);
    indices = std::move(other.indices);

    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
  }
  return *this;
}

OpenGLMesh::~OpenGLMesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void OpenGLMesh::SetupMesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Convert vertices to GLM format for OpenGL
  std::vector<glm::vec3> glmVertices;
  std::vector<glm::vec3> glmNormals;
  std::vector<glm::vec2> glmTexCoords;
  for (const auto &vertex : vertices) {
    glmVertices.push_back(ConvertToGLMVec3(vertex.position));
    glmNormals.push_back(ConvertToGLMVec3(vertex.normal));
    glmTexCoords.push_back(ConvertToGLMVec2(vertex.texCoords));
  }

  // Combine converted data into a single buffer
  std::vector<float> bufferData;
  for (size_t i = 0; i < vertices.size(); ++i) {
    bufferData.insert(bufferData.end(),
                      {glmVertices[i].x, glmVertices[i].y, glmVertices[i].z});
    bufferData.insert(bufferData.end(),
                      {glmNormals[i].x, glmNormals[i].y, glmNormals[i].z});
    bufferData.insert(bufferData.end(), {glmTexCoords[i].x, glmTexCoords[i].y});
  }

  glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float),
               bufferData.data(), GL_STATIC_DRAW);

  // Vertex attribute setup
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));

  glBindVertexArray(0);
}

void OpenGLMesh::Draw() const {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace render
} // namespace velopraEngine