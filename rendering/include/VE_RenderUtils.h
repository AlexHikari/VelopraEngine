#ifndef VE_RENDERING_UTILS_H
#define VE_RENDERING_UTILS_H

#include "VE_RendererAPI.h"

namespace velopraEngine {

namespace core {

struct Vector3;
struct Vector2;
struct Matrix4;
struct Quaternion;

}; // namespace core

namespace render {

VELOPRARENDERER_API glm::vec2 ConvertToGLMVec2(const core::Vector2 &vec);
VELOPRARENDERER_API core::Vector2 ConvertFromGLMVec2(const glm::vec2 &vec);
VELOPRARENDERER_API glm::vec3 ConvertToGLMVec3(const core::Vector3 &vec);
VELOPRARENDERER_API core::Vector3 ConvertFromGLMVec3(const glm::vec3 &vec);
VELOPRARENDERER_API glm::mat4 ConvertToGLMMat4(const core::Matrix4 &mat);
VELOPRARENDERER_API core::Matrix4 ConvertFromGLMMat4(const glm::mat4 &glmMat);
VELOPRARENDERER_API glm::quat ConvertToGLMQuat(const core::Quaternion &quat);
VELOPRARENDERER_API core::Quaternion ConvertFromGLMQuat(const glm::quat &quat);

} // namespace render
} // namespace velopraEngine

#endif // VE_RENDERING_UTILS_H