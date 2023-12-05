#include "VE_InputEventGenerator.h"

namespace velopraEngine {
namespace input {

InputEventGenerator &InputEventGenerator::Instance() {
  static InputEventGenerator instance;
  return instance;
}

void InputEventGenerator::Update() {
  CheckDoubleClicks();
  CheckLongPresses();
  ResetTemporaryStates();
}

bool InputEventGenerator::IsKeyPressed(KeyCode key) const {
  auto it = keyStates.find(key);
  return it != keyStates.end() && it->second;
}

bool InputEventGenerator::IsKeyReleased(KeyCode key) const {
  auto it = keyStates.find(key);
  return it != keyStates.end() && !it->second;
}

bool InputEventGenerator::IsMouseButtonPressed(MouseCode button) const {
  auto it = mouseButtonStates.find(button);
  return it != mouseButtonStates.end() && it->second;
}

std::pair<float, float> InputEventGenerator::GetMousePosition() const {
  return {mouseX, mouseY};
}

float InputEventGenerator::GetMouseX() const { return mouseX; }

float InputEventGenerator::GetMouseY() const { return mouseY; }

void InputEventGenerator::UpdateKeyState(KeyCode key, bool pressed) {
  keyStates[key] = pressed;
  justPressedKeys[key] = pressed;
}

void InputEventGenerator::UpdateMouseButtonState(MouseCode button,
                                                 bool pressed) {
  mouseButtonStates[button] = pressed;
  if (pressed) {
    lastClickTime[button] = std::chrono::high_resolution_clock::now();
  }
}

void InputEventGenerator::UpdateMousePosition(float x, float y) {
  mouseX = x;
  mouseY = y;
}

void InputEventGenerator::CheckDoubleClicks() {
  auto now = std::chrono::high_resolution_clock::now();
  const std::chrono::milliseconds DOUBLE_CLICK_THRESHOLD =
      std::chrono::milliseconds(500);

  for (auto &[button, lastTime] : lastClickTime) {
    if (mouseButtonStates[button]) {
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime);
      if (duration <= DOUBLE_CLICK_THRESHOLD) {
        // Double-click detected
        // Handle double-click event here
        // ...
      }
      lastTime = now; // Update last click time
    }
  }
}

void InputEventGenerator::CheckLongPresses() {
  auto now = std::chrono::high_resolution_clock::now();
  const std::chrono::milliseconds LONG_PRESS_THRESHOLD =
      std::chrono::milliseconds(1000);

  for (auto &[key, startTime] : keyPressStartTime) {
    if (keyStates[key]) {
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
          now - startTime);
      if (duration >= LONG_PRESS_THRESHOLD) {
        // Long press detected
        // Handle long press event here
        // ...
      }
    } else {
      startTime = now; // Reset start time when key is released
    }
  }
}

void InputEventGenerator::ResetTemporaryStates() {
  for (auto &[key, flag] : justPressedKeys) {
    flag = false;
  }
  // Reset other temporary states as needed
  // ...
}

} // namespace input
} // namespace velopraEngine
