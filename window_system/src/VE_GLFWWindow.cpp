#include "VE_GLFWWindow.h"
#include "VE_Core.h"
#include "VE_InputTypes.h"
#include "VE_InputEventGenerator.h"

namespace velopraEngine {
namespace window {

VE_GLFWWindow::VE_GLFWWindow()
    : glfwWindow(nullptr) {}

VE_GLFWWindow::~VE_GLFWWindow() {
  if (glfwWindow) {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
  }
}

void VE_GLFWWindow::Initialize(const std::string &title, int width,
                               int height) {
  if (!glfwInit()) {
    VELOPRA_CORE_ERROR("Failed to initialize GLFW");
    return;
  }

  glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!glfwWindow) {
    VELOPRA_CORE_ERROR("Failed to create GLFW window");
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(glfwWindow);
  glfwSwapInterval(1); // Enable vsync

  // Set GLFW callbacks
  glfwSetWindowUserPointer(glfwWindow, this);
  glfwSetWindowSizeCallback(
      glfwWindow, [](GLFWwindow *window, int width, int height) {
        auto event = std::make_shared<core::WindowResizeEvent>(width, height);
        core::Core::Instance().GetEventQueue()->PushEvent(event);
      });
}

void VE_GLFWWindow::Update() {
  glfwPollEvents();
  // Polling-based input updates
  for (int key = 0; key <= GLFW_KEY_LAST; ++key) {
    auto state = glfwGetKey(glfwWindow, key);
    bool pressed = (state == GLFW_PRESS);
    input::InputEventGenerator::Instance().UpdateKeyState(
        static_cast<input::KeyCode>(key), pressed);
  }
  for (int button = 0; button <= GLFW_MOUSE_BUTTON_LAST; ++button) {
    auto state = glfwGetMouseButton(glfwWindow, button);
    bool pressed = (state == GLFW_PRESS);
    input::InputEventGenerator::Instance().UpdateMouseButtonState(
        static_cast<input::MouseCode>(button), pressed);
  }
  double mouseX, mouseY;
  glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);
  input::InputEventGenerator::Instance().UpdateMousePosition(
      static_cast<float>(mouseX), static_cast<float>(mouseY));

  // Swap buffers if using OpenGL
  glfwSwapBuffers(glfwWindow);
}

bool VE_GLFWWindow::ShouldClose() const {
  return glfwWindow && glfwWindowShouldClose(glfwWindow);
}

void VE_GLFWWindow::SetEventCallback(
    const std::function<void(std::shared_ptr<core::Event>)> &callback) {
  eventCallback = callback;
}

GLFWwindow *VE_GLFWWindow::GetNativeWindow() const { return glfwWindow; }


} // namespace window
} // namespace velopraEngine
