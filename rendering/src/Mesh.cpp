#include "Mesh.h"
#include "pch.h"

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<GLuint> &indices)
    : vertices(vertices), indices(indices) {
  SetupMesh();
}

// Move constructor
Mesh::Mesh(Mesh &&other) noexcept
    : VAO(other.VAO), VBO(other.VBO), EBO(other.EBO),
      vertices(std::move(other.vertices)), indices(std::move(other.indices)) {
  other.VAO = 0;
  other.VBO = 0;
  other.EBO = 0;
}

// Move assignment operator
Mesh &Mesh::operator=(Mesh &&other) noexcept {
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

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Mesh::SetupMesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  // Load data into vertex buffers
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);

  // Vertex attribute setup
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, texCoords));

  glBindVertexArray(0);
}

void Mesh::Draw() const {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}