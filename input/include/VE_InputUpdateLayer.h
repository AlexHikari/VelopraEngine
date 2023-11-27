#ifndef VE_INPUT_UPDATE_LAYER_H
#define VE_INPUT_UPDATE_LAYER_H

#include "VE_InputAPI.h"
#include "VE_InputEventGenerator.h"
#include "VE_Layer.h"
#include <memory>

namespace velopraEngine {
namespace input {

class VELOPRAINPUT_API InputUpdateLayer : public core::Layer {
public:
  InputUpdateLayer();

  void OnUpdate();

private:
  std::unique_ptr<InputEventGenerator> inputEventGenerator;
};

} // namespace input
} // namespace velopraEngine

#endif // VE_INPUT_UPDATE_LAYER_H
