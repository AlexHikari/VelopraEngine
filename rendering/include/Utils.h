#ifndef VE_RENDERING_UTILS_H
#define VE_RENDERING_UTILS_H

#include "RendererAPI.h"

namespace VelopraEngine {

namespace Core {
struct Vector3;
struct Vector2;
}; // namespace Core

namespace Utils {
RENDERER_API glm::vec3 ConvertToGLMVec3(const Core::Vector3 &vec);
RENDERER_API Core::Vector3 ConvertFromGLMVec3(const glm::vec3 &vec);
} // namespace Utils
} // namespace VelopraEngine

#endif // VE_RENDERING_UTILS_H