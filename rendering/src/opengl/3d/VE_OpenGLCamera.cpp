#include "VE_pch.h"
#include "opengl/3d/VE_OpenGLCamera.h"
#include "VE_RenderUtils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace velopraEngine {
namespace render {

OpenGLCamera::OpenGLCamera(glm::vec3 position, glm::vec3 up, float yaw,
                           float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f),
      MouseSensitivity(0.1f), Zoom(45.0f) {
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

core::Matrix4 OpenGLCamera::GetViewMatrix() const {
  return core::Matrix4(ConvertFromGLMMat4(glm::lookAt(Position, Position + Front, Up)));
}

core::Matrix4 OpenGLCamera::GetProjectionMatrix() const {
  // Perspective parameters: Field of View, aspect ratio, near plane, and far
  // plane
  float fov = glm::radians(Zoom); // Convert Zoom angle to radians
  float aspectRatio = static_cast<float>(GetWindowWidth()) / GetWindowHeight();
  float nearPlane = 0.1f;
  float farPlane = 100.0f;

  glm::mat4 projection =
      glm::perspective(fov, aspectRatio, nearPlane, farPlane);
  return core::Matrix4(ConvertFromGLMMat4(
      projection)); // Assuming you have a conversion function
}

void OpenGLCamera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
  float velocity = MovementSpeed * deltaTime;
  if (direction == FORWARD)
    Position += Front * velocity;
  if (direction == BACKWARD)
    Position -= Front * velocity;
  if (direction == LEFT)
    Position -= Right * velocity;
  if (direction == RIGHT)
    Position += Right * velocity;
}

void OpenGLCamera::ProcessMouseMovement(float xoffset, float yoffset,
                          bool constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  updateCameraVectors();
}

void OpenGLCamera::ProcessMouseScroll(float yoffset) {
  Zoom -= yoffset;
  if (Zoom < 1.0f)
    Zoom = 1.0f;
  if (Zoom > 45.0f)
    Zoom = 45.0f;
}

void OpenGLCamera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}

} // namespace render
} // namespace velopraEngine