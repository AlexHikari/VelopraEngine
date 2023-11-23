#ifndef VE_OPENGL_RENDERER_H
#define VE_OPENGL_RENDERER_H

#include "VE_ICamera.h"
#include "VE_IRenderer.h"
#include "VE_ITexture.h"
#include "VE_IShader.h"
#include "VE_IModel.h"
#include "VE_IWindowSizeObserver.h"
#include "VE_RendererAPI.h"
#include <GL/glew.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API OpenGLRenderer : public IWindowSizeObserver,
                                           public IRenderer {
public:
  OpenGLRenderer();
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
  float aspectRatio;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_RENDERER_H
