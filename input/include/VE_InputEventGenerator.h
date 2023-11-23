#ifndef VE_INPUT_EVENT_GENERATOR_H
#define VE_INPUT_EVENT_GENERATOR_H

#include "VE_InputAPI.h"
#include "VE_InputTypes.h"
#include "VE_Event.h"
#include <unordered_map>
#include <utility>

namespace velopraEngine {
namespace input {

class VE_INPUT_API_H InputEventGenerator {
public:
  void Update(); // Called every frame to update input states

  // Keyboard state methods
  bool IsKeyPressed(KeyCode key) const;
  bool IsKeyReleased(KeyCode key) const;

  // Mouse state methods
  bool IsMouseButtonPressed(MouseCode button) const;
  std::pair<float, float> GetMousePosition() const;
  float GetMouseX() const;
  float GetMouseY() const;

private:
  std::unordered_map<KeyCode, bool> keyStates;
  std::unordered_map<MouseCode, bool> mouseButtonStates;
  float mouseX, mouseY;

  // Methods to update internal state
  void UpdateKeyState(KeyCode key, bool pressed);
  void UpdateMouseButtonState(MouseCode button, bool pressed);
  void UpdateMousePosition(float x, float y);
};

} // namespace input
} // namespace velopraEngine

#endif // VE_INPUT_EVENT_GENERATOR_H
