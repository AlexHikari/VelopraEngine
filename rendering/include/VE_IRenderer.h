#ifndef VE_IRENDERER_H
#define VE_IRENDERER_H

#include "VE_ITexture.h"
#include "VE_RendererAPI.h"
#include <memory>

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void Initialize() = 0;
  virtual void BeginFrame() = 0;
  virtual void RenderFrame() = 0;
  virtual std::shared_ptr<ITexture>
  LoadTexture(const std::string &filePath) = 0;
  virtual void OnWindowSizeChanged(int width, int height) = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_IRENDERER_H