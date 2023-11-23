#include "VE_InputUpdateLayer.h"

namespace velopraEngine {
namespace input {

InputUpdateLayer::InputUpdateLayer()
    : Layer("InputUpdateLayer"),
      inputEventGenerator(std::make_unique<InputEventGenerator>()) {}

void InputUpdateLayer::OnUpdate() { inputEventGenerator->Update(); }

} // namespace input
} // namespace velopraEngine