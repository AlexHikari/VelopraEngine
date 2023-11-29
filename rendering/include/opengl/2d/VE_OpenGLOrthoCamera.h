#ifndef VE_OPENGL_ORTHO_CAMERA_H
#define VE_OPENGL_ORTHO_CAMERA_H

#include "interfaces/VE_ICamera.h"

namespace velopraEngine {
namespace render {

class OpenGLOrthoCamera : public ICamera {
public:
  OpenGLOrthoCamera(float left, float right, float bottom, float top);

  core::Matrix4 GetViewMatrix() const override;
  core::Matrix4 GetProjectionMatrix() const override;

  void ProcessKeyboard(Camera_Movement direction, float deltaTime) override;
  void ProcessMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true) override;
  void ProcessMouseScroll(float yoffset) override;

  void SetPosition(const glm::vec2 &position);
  void SetZoomLevel(float level);
  void SetOrthoBounds(float left, float right, float bottom, float top);

private:
  glm::vec2 Position;
  float ZoomLevel;
  float Left, Right, Bottom, Top;
  float MouseSensitivity;
  float ZoomSensitivity;
  float MovementSpeed;
  glm::mat4 ProjectionMatrix;

  void UpdateProjection();
};

} // namespace render
} // namespace velopraEngine

#endif // VE_OPENGL_ORTHO_CAMERA_H