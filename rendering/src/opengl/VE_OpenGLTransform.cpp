#include "VE_pch.h"
#include "opengl/VE_OpenGLTransform.h"

namespace velopraEngine {
namespace render {

OpenGLTransform::OpenGLTransform()
    : m_position(0.0f), m_rotation(glm::quat()), m_scale(1.0f) {}

core::Matrix4 OpenGLTransform::GetModelMatrix() const {
  glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
  model *= glm::toMat4(m_rotation);
  model = glm::scale(model, m_scale);
  return ConvertFromGLMMat4(model);
}

void OpenGLTransform::SetPosition(const core::Vector3 &pos) {
  m_position = ConvertToGLMVec3(pos);
}

void OpenGLTransform::SetRotation(const core::Quaternion &rot) {
  m_rotation = ConvertToGLMQuat(rot);
}

void OpenGLTransform::SetScale(const core::Vector3 &scale) {
  m_scale = ConvertToGLMVec3(scale);
}

core::Vector3 OpenGLTransform::GetPosition() const {
  return ConvertFromGLMVec3(m_position);
}

core::Quaternion OpenGLTransform::GetRotation() const {
  return ConvertFromGLMQuat(m_rotation);
}

core::Vector3 OpenGLTransform::GetScale() const {
  return ConvertFromGLMVec3(m_scale);
}

core::Vector3 OpenGLTransform::GetForwardDirection() const {
  return ConvertFromGLMVec3(m_rotation * glm::vec3(0, 0, -1));
}

core::Vector3 OpenGLTransform::GetUpDirection() const {
  return ConvertFromGLMVec3(m_rotation * glm::vec3(0, 1, 0));
}

core::Vector3 OpenGLTransform::GetRightDirection() const {
  return ConvertFromGLMVec3(m_rotation * glm::vec3(1, 0, 0));
}

} // namespace render
} // namespace velopraEngine
