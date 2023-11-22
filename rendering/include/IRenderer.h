#ifndef VE_IRENDERER_H
#define VE_IRENDERER_H

#include "ITexture.h"
#include <memory>

class IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void Initialize() = 0;
  virtual void BeginFrame() = 0;
  virtual void RenderFrame() = 0;
  virtual std::shared_ptr<ITexture>
  LoadTexture(const std::string &filePath) = 0;
  virtual void OnWindowSizeChanged(int width, int height) = 0;
};

#endif // VE_IRENDERER_H