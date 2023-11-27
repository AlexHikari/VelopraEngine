#ifndef VE_RENDER_TYPE
#define VE_RENDER_TYPE

#include "VE_UIApi.h"

namespace velopraEngine {
namespace ui {

enum class VELOPRAUI_API RenderType {
  OpenGL,
  Vulkan,
  DirectX
  // Add other render types if needed
};

} // namespace ui
} // namespace velopraEngine

#endif // VE_RENDER_TYPE
