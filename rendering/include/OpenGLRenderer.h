#ifndef VE_OPENGL_RENDERER_H
#define VE_OPENGL_RENDERER_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "IWindowSizeObserver.h"

class OpenGLRenderer : public IWindowSizeObserver {
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void Initialize();
	void BeginFrame();
	void RenderFrame();
	GLuint LoadTexture(const std::string& filePath);
	void UpdateProjectionMatrix(int width, int height);

	virtual void OnWindowSizeChanged(int width, int height) override;

private:
	std::unordered_map<std::string, GLuint> textureCache;
	Shader* shader;
	Model* model;
	Camera* camera;
	glm::mat4 projectionMatrix;
	float aspectRatio;
};

#endif // VE_OPENGL_RENDERER_H
