#ifndef VE_ITRANSFORM_H
#define VE_ITRANSFORM_H

#include "VE_Math.h"

namespace velopraEngine {
namespace render {

class ITransform {
public:
  virtual ~ITransform() = default;

  virtual void SetPosition(const core::Vector3 &pos) = 0;
  virtual void SetRotation(const core::Quaternion &rot) = 0;
  virtual void SetScale(const core::Vector3 &scale) = 0;

  virtual core::Vector3 GetPosition() const = 0;
  virtual core::Quaternion GetRotation() const = 0;
  virtual core::Vector3 GetScale() const = 0;

  virtual core::Vector3 GetForwardDirection() const = 0;
  virtual core::Vector3 GetUpDirection() const = 0;
  virtual core::Vector3 GetRightDirection() const = 0;

  virtual core::Matrix4 GetModelMatrix() const = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_ITRANSFORM_H