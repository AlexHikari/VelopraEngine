#include "Utils.h"
#include "pch.h"

namespace VelopraEngine {
namespace Utils {
glm::vec3 ConvertToGLMVec3(const Core::Vector3 &vec) {
  return glm::vec3(vec.x, vec.y, vec.z);
}

Core::Vector3 ConvertFromGLMVec3(const glm::vec3 &vec) {
  return Core::Vector3(vec.x, vec.y, vec.z);
}

} // namespace Utils
} // namespace VelopraEngine
