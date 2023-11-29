#ifndef VE_OPENGLTRANSFORM_H
#define VE_OPENGLTRANSFORM_H

#include "interfaces/VE_ITransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace velopraEngine {
namespace render {

class OpenGLTransform : public ITransform {
public:
  OpenGLTransform();

  void SetPosition(const core::Vector3 &pos) override;
  void SetRotation(const core::Quaternion &rot) override;
  void SetScale(const core::Vector3 &scale) override;

  core::Vector3 GetPosition() const override;
  core::Quaternion GetRotation() const override;
  core::Vector3 GetScale() const override;

  core::Vector3 GetForwardDirection() const override;
  core::Vector3 GetUpDirection() const override;
  core::Vector3 GetRightDirection() const override;

  core::Matrix4 GetModelMatrix() const override;

private:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGLTRANSFORM_H
