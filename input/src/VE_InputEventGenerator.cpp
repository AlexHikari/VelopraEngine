#include "VE_InputEventGenerator.h"
#include "VE_InputTypes.h"
#include "VE_Core.h"
#include "VE_KeyboardEvent.h"
#include "VE_MouseEvent.h"

namespace velopraEngine {
namespace input {

void InputEventGenerator::Update() {}

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
}

void InputEventGenerator::UpdateMouseButtonState(MouseCode button,
                                                 bool pressed) {
  mouseButtonStates[button] = pressed;
}

void InputEventGenerator::UpdateMousePosition(float x, float y) {
  mouseX = x;
  mouseY = y;
}

} // namespace input
} // namespace velopraEngine