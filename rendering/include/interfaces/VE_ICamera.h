#ifndef VE_ICAMERA_H
#define VE_ICAMERA_H

#include "VE_Math.h"
#include "VE_RendererAPI.h"

namespace velopraEngine {
namespace render {

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class VELOPRARENDERER_API ICamera {
public:
  virtual ~ICamera() = default;

  virtual core::Matrix4 GetViewMatrix() const = 0;
  virtual core::Matrix4 GetProjectionMatrix() const = 0;
  virtual void ProcessKeyboard(Camera_Movement direction, float deltaTime) = 0;
  virtual void ProcessMouseMovement(float xoffset, float yoffset,
                                    bool constrainPitch = true) = 0;
  virtual void ProcessMouseScroll(float yoffset) = 0;
  virtual void Update(float deltaTime) = 0;
  int GetWindowHeight() const { return windowHeigth; }
  int GetWindowWidth() const { return windowWidth; }

private:
  int windowWidth;
  int windowHeigth;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_ICAMERA_H
