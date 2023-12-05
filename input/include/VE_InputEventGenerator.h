#ifndef VE_INPUT_EVENT_GENERATOR_H
#define VE_INPUT_EVENT_GENERATOR_H

#include "VE_InputAPI.h"
#include "VE_InputTypes.h"
#include <chrono>
#include <unordered_map>
#include <utility>

namespace velopraEngine {
namespace input {

class VELOPRAINPUT_API InputEventGenerator {
public:
  static InputEventGenerator &Instance();

  void UpdateKeyState(KeyCode key, bool pressed);
  void UpdateMouseButtonState(MouseCode button, bool pressed);
  void UpdateMousePosition(float x, float y);

  void Update();

  bool IsKeyPressed(KeyCode key) const;
  bool IsKeyReleased(KeyCode key) const;
  bool IsMouseButtonPressed(MouseCode button) const;
  std::pair<float, float> GetMousePosition() const;
  float GetMouseX() const;
  float GetMouseY() const;

private:
  std::unordered_map<KeyCode, bool> keyStates;
  std::unordered_map<MouseCode, bool> mouseButtonStates;
  std::unordered_map<MouseCode,
                     std::chrono::high_resolution_clock::time_point>
      lastClickTime;
  std::unordered_map<KeyCode,
                     std::chrono::high_resolution_clock::time_point>
      keyPressStartTime;
  std::unordered_map<KeyCode, bool> justPressedKeys;
  float mouseX, mouseY;

  void CheckDoubleClicks();
  void CheckLongPresses();
  void ResetTemporaryStates();
};

} // namespace input
} // namespace velopraEngine

#endif // VE_INPUT_EVENT_GENERATOR_H
