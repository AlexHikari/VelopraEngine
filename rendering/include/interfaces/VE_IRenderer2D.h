#ifndef VE_IRENDERER2D_H
#define VE_IRENDERER2D_H

#include "VE_ITexture.h"
#include "interfaces/VE_IRenderer.h"
#include "VE_Math.h"
#include <memory>

namespace velopraEngine {
namespace render {

class IRenderer2D : public IRenderer {
public:
  virtual ~IRenderer2D() = default;

  virtual void AddQuad(const core::Vector2 &position, const core::Vector2 &size,
                       const core::Vector4 &color, const float rotation,
                       std::shared_ptr<ITexture> texture) = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_IRENDERER2D_H
