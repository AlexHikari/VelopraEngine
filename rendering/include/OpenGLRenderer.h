#ifndef VE_OPENGL_RENDERER_H
#define VE_OPENGL_RENDERER_H

#include "Camera.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "IWindowSizeObserver.h"
#include "Model.h"
#include "RendererAPI.h"
#include "Shader.h"
#include <GL/glew.h>
#include <string>
#include <unordered_map>

class RENDERER_API OpenGLRenderer : public IWindowSizeObserver,
                                    public IRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer() = default;

  void Initialize() override;
  void BeginFrame() override;
  void RenderFrame() override;
  virtual std::shared_ptr<ITexture>
  LoadTexture(const std::string &filePath) override;
  virtual void OnWindowSizeChanged(int width, int height) override;

  void UpdateProjectionMatrix(int width, int height);

private:
  std::unordered_map<std::string, std::shared_ptr<ITexture>> textureCache;
  std::unique_ptr<Shader> shader;
  std::unique_ptr<Model> model;
  std::unique_ptr<Camera> camera;
  glm::mat4 projectionMatrix;
  float aspectRatio;
};

#endif // VE_OPENGL_RENDERER_H
