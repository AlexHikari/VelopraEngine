// VE_IWindow.h

#ifndef VE_IWINDOW_H
#define VE_IWINDOW_H

#include "VE_WindowAPI.h"
#include "VE_Event.h"
#include <functional>
#include <string>
#include <memory>

namespace velopraEngine {
namespace window {

class VELOPRAWINDOW_API IWindow {
public:
  virtual ~IWindow() = default;

  virtual void Initialize(const std::string &title, int width, int height) = 0;
  virtual void Update() = 0;
  virtual bool ShouldClose() const = 0;
  virtual void SetEventCallback(
      const std::function<void(std::shared_ptr<core::Event>)> &callback) = 0;
};

} // namespace window
} // namespace velopraEngine

#endif // VE_IWINDOW_H