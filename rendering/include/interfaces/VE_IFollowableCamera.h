#ifndef VE_IFOLLOWABLECAMERA_H
#define VE_IFOLLOWABLECAMERA_H

#include "interfaces/VE_ICamera.h"
#include "VE_RendererAPI.h"

namespace velopraEngine {
namespace render {

class VELOPRARENDERER_API IFollowableCamera : public ICamera {
public:
  virtual ~IFollowableCamera() = default;

  virtual void SetFollowCallback(
      const std::function<void(IFollowableCamera &, float)> &callback) = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_IFOLLOWABLECAMERA_H
