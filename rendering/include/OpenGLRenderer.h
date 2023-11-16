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

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	// Method to register callbacks
	void RegisterInputCallbacks();

private:
	GLFWwindow* window;
	std::unordered_map<std::string, GLuint> textureCache;
	Shader* shader;
	Model* model;
	Camera* camera;
	glm::mat4 projectionMatrix;
	float aspectRatio;
};

#endif // VE_OPENGL_RENDERER_H
