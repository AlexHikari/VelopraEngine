#ifndef VE_INPUT_UPDATE_LAYER_H
#define VE_INPUT_UPDATE_LAYER_H

#include "VE_InputAPI.h"
#include "InputEventGenerator.h"
#include "VE_Layer.h"
#include <memory>

namespace velopraEngine {
namespace input {

class VE_INPUT_API_H InputUpdateLayer : public core::Layer {
public:
  InputUpdateLayer()
      : Layer("InputUpdateLayer"),
        inputEventGenerator(std::make_unique<InputEventGenerator>()) {}

  void OnUpdate() override { inputEventGenerator->Update(); }

private:
  std::unique_ptr<InputEventGenerator> inputEventGenerator;
};

} // namespace input
} // namespace velopraEngine

#endif // VE_INPUT_UPDATE_LAYER_H
