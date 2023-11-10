#ifndef VELOPRA_MESH_H
#define VELOPRA_MESH_H

#include <GL/glew.h>
#include <vector>

struct Vertex {
	// Position
	glm::vec3 position;
	// Normal
	glm::vec3 normal;
	// Texture Coordinates
	glm::vec2 texCoords;
};

class Mesh {
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
	~Mesh();

	void Draw() const;

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint VAO, VBO, EBO;

	void SetupMesh();
};