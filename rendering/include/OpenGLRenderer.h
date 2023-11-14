#ifndef VE_OPENGL_RENDERER_H
#define VE_OPENGL_RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

class OpenGLRenderer {
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void Initialize();
	void Shutdown();
	void BeginFrame();
	void RenderFrame();
	void EndFrame();
	GLuint LoadTexture(const std::string& filePath);
	bool WindowShouldClose() const;
	void UpdateProjectionMatrix(int width, int height);

private:
	GLFWwindow* window;
	std::unordered_map<std::string, GLuint> textureCache;
	Shader* shader;
	Model* model;
	Camera* camera;
	glm::mat4 projectionMatrix;
	float aspectRatio;

	void RenderTestTriangle();
	void RenderTestCube();
	void LogMatrix(const std::string& name, const glm::mat4& mat);
};

#endif // VE_OPENGL_RENDERER_H
