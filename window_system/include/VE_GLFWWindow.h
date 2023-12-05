#ifndef VE_GLFW_WINDOW_H
#define VE_GLFW_WINDOW_H

#include "VE_WindowAPI.h"
#include "VE_IWindow.h"
#include "VE_Event.h"
#include "VE_LoggerMacros.h"
#include "VE_WindowEvent.h"
#include "VE_KeyboardEvent.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>

namespace velopraEngine {
namespace window {

class VELOPRAWINDOW_API VE_GLFWWindow : public IWindow {
public:
  VE_GLFWWindow();
  ~VE_GLFWWindow() override;

  void Initialize(const std::string &title, int width, int height) override;
  void Update() override;
  bool ShouldClose() const override;
  void SetEventCallback(
      const std::function<void(std::shared_ptr<core::Event>)> &callback) override;
  GLFWwindow *GetNativeWindow() const;

private:
  GLFWwindow *glfwWindow;
  std::function<void(std::shared_ptr<core::Event>)> eventCallback;
};

} // namespace window
} // namespace velopraEngine

#endif // VE_GLFW_WINDOW_H
