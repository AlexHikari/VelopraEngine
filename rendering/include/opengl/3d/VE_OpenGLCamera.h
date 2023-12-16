#ifndef VE_CAMERA_H
#define VE_CAMERA_H


#include "interfaces/VE_ICamera.h"
#include "VE_RendererAPI.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API OpenGLCamera : public ICamera {
public:
  OpenGLCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f,
               float pitch = 0.0f);

  core::Matrix4 GetViewMatrix() const override;
  core::Matrix4 GetProjectionMatrix() const override;

  void ProcessKeyboard(Camera_Movement direction, float deltaTime) override;
  void ProcessMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true) override;
  void ProcessMouseScroll(float yoffset) override;
  void Update(float deltaTime) override;

private:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  float Yaw;
  float Pitch;
  float MovementSpeed;
  float MouseSensitivity;
  float ZoomSensitivity;
  float Zoom;

  void updateCameraVectors();
};

} // namespace render
} // namespace velopraEngine

#endif // VE_CAMERA_H
