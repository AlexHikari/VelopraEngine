#include "VE_RenderUtils.h"
#include "VE_pch.h"

namespace velopraEngine {
namespace render {

glm::vec2 ConvertToGLMVec2(const core::Vector2 &vec) {
  return glm::vec2(vec.x, vec.y);
}

core::Vector2 ConvertFromGLMVec2(const glm::vec2 &vec) {
  return core::Vector2(vec.x, vec.y);
}

glm::vec3 ConvertToGLMVec3(const core::Vector3 &vec) {
  return glm::vec3(vec.x, vec.y, vec.z);
}

core::Vector3 ConvertFromGLMVec3(const glm::vec3 &vec) {
  return core::Vector3(vec.x, vec.y, vec.z);
}

glm::mat4 ConvertToGLMMat4(const core::Matrix4 &mat) {
  glm::mat4 glmMat;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      glmMat[i][j] = mat.m[i][j];
    }
  }
  return glmMat;
}

core::Matrix4 ConvertFromGLMMat4(const glm::mat4 &glmMat) {
  core::Matrix4 mat;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mat.m[i][j] = glmMat[i][j];
    }
  }
  return mat;
}

glm::quat ConvertToGLMQuat(const core::Quaternion &quat) {
  return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

core::Quaternion ConvertFromGLMQuat(const glm::quat &glmQuat) {
  return core::Quaternion(glmQuat.w, glmQuat.x, glmQuat.y, glmQuat.z);
}

} // namespace render
} // namespace velopraEngine
