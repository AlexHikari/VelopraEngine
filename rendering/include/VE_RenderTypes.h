#ifndef VE_RENDER_TYPE
#define VE_RENDER_TYPE

#include "VE_RendererAPI.h"

namespace velopraEngine {
namespace render {

enum class VELOPRARENDERER_API RenderType {
  OpenGL,
  Vulkan,
  DirectX,
  Metal
};

enum class VELOPRARENDERER_API DimensionType { TwoD, ThreeD };

} // namespace core
} // namespace velopraEngine

#endif // VE_RENDER_TYPE
