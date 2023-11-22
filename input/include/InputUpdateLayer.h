#ifndef VE_INPUT_UPDATE_LAYER_H
#define VE_INPUT_UPDATE_LAYER_H

#include "InputEventGenerator.h"
#include "VE_Layer.h"
#include <memory>

class InputUpdateLayer : public Layer {
public:
  InputUpdateLayer()
      : Layer("InputUpdateLayer"),
        inputEventGenerator(std::make_unique<InputEventGenerator>()) {}

  void OnUpdate() override { inputEventGenerator->Update(); }

private:
  std::unique_ptr<InputEventGenerator> inputEventGenerator;
};

#endif // VE_INPUT_UPDATE_LAYER_H
