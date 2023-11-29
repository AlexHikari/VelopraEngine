#ifndef VE_OPENGL_RENDERER_H
#define VE_OPENGL_RENDERER_H

#include <GL/glew.h>
#include "interfaces/VE_ICamera.h"
#include "interfaces/VE_IRenderer.h"
#include "interfaces/VE_ITexture.h"
#include "interfaces/VE_IShader.h"
#include "interfaces/VE_IModel.h"
#include "interfaces/VE_IWindowSizeObserver.h"
#include "VE_RendererAPI.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API OpenGLRenderer : public IWindowSizeObserver,
                                           public IRenderer {
public:
  OpenGLRenderer(int width, int height);
  ~OpenGLRenderer() = default;

  void Initialize() override;
  void BeginFrame() override;
  void RenderFrame() override;
  std::shared_ptr<ITexture> LoadTexture(const std::string &filePath) override;
  void OnWindowSizeChanged(int width, int height) override;

  void UpdateProjectionMatrix(int width, int height);

private:
  std::unordered_map<std::string, std::shared_ptr<ITexture>> textureCache;
  std::unique_ptr<IShader> shader;
  std::unique_ptr<IModel> model;
  std::unique_ptr<ICamera> camera;
  core::Matrix4 projectionMatrix;
  int width, height;
  float aspectRatio;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_RENDERER_H
