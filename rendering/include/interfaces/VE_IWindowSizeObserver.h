#ifndef VE_WINDOW_SIZE_OBSERVER_H
#define VE_WINDOW_SIZE_OBSERVER_H

namespace velopraEngine {
namespace render {

class IWindowSizeObserver {
public:
  virtual ~IWindowSizeObserver() = default;
  virtual void OnWindowSizeChanged(int width, int height) = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_WINDOW_SIZE_OBSERVER_H