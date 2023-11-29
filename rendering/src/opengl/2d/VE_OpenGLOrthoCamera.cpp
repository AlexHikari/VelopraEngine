#include "opengl/2d/VE_OpenGLOrthoCamera.h"

namespace velopraEngine {
namespace render {

OpenGLOrthoCamera::OpenGLOrthoCamera(float left, float right, float bottom,
                                     float top)
    : Position(0.0f, 0.0f), ZoomLevel(1.0f), Left(left), Right(right),
      Bottom(bottom), Top(top), MouseSensitivity(0.02f),
      ZoomSensitivity(0.02f) {
  UpdateProjection();
}

core::Matrix4 OpenGLOrthoCamera::GetViewMatrix() const {
  // it could be a translation matrix if the camera supports panning.
return core::Matrix4(); // Identity matrix
}

void OpenGLOrthoCamera::ProcessKeyboard(Camera_Movement direction,
                                        float deltaTime) {
  float velocity = MovementSpeed * deltaTime;
  switch (direction) {
  case FORWARD:
    Position.y -= velocity; // Move up
    break;
  case BACKWARD:
    Position.y += velocity; // Move down
    break;
  case LEFT:
    Position.x -= velocity; // Move left
    break;
  case RIGHT:
    Position.x += velocity; // Move right
    break;
  }
}

void OpenGLOrthoCamera::ProcessMouseMovement(float xoffset, float yoffset,
                                             bool constrainPitch) {
  Position.x -= xoffset * MouseSensitivity;
  Position.y += yoffset * MouseSensitivity;
}

void OpenGLOrthoCamera::ProcessMouseScroll(float yoffset) {
  ZoomLevel -= yoffset * ZoomSensitivity;
  ZoomLevel = std::max(ZoomLevel, 0.1f);
  UpdateProjection();
}

void OpenGLOrthoCamera::SetPosition(const glm::vec2 &position) {
  Position = position;
}

void OpenGLOrthoCamera::SetZoomLevel(float level) {
  ZoomLevel = level;
  UpdateProjection();
}

void OpenGLOrthoCamera::UpdateProjection() {
  Left = -ZoomLevel;
  Right = ZoomLevel;
  Bottom = -ZoomLevel;
  Top = ZoomLevel;
}

void OpenGLOrthoCamera::SetOrthoBounds(float left, float right, float bottom,
                                       float top) {
  ProjectionMatrix = glm::ortho(left, right, bottom, top);
}

core::Matrix4 OpenGLOrthoCamera::GetProjectionMatrix() const {
  return core::Matrix4(ConvertFromGLMMat4(ProjectionMatrix));
}

} // namespace render
} // namespace velopraEngine
