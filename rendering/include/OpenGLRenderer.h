// OpenGLRenderer.h
#ifndef VELOPRA_ENGINE_OPENGL_RENDERER_H
#define VELOPRA_ENGINE_OPENGL_RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VE_Logger.h"

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

private:
	GLFWwindow* window;
	std::unordered_map<std::string, GLuint> textureCache;
};

#endif // OPENGL_RENDERER_H
