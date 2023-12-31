#ifndef VE_CORE_H
#define VE_CORE_H

#include "VE_CoreAPI.h"
#include "VE_EventBus.h"
#include "VE_EventQueue.h"
#include "VE_Layer.h"
#include "VE_LayerStack.h"
#include <chrono>

namespace velopraEngine {
namespace core {

class VELOPRACORE_API Core {
public:
  static Core &Instance();

  EventQueue *GetEventQueue();
  EventBus *GetEventBus();

  Core(const Core &) = delete;
  Core &operator=(const Core &) = delete;

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *overlay);

  LayerStack::iterator begin();
  LayerStack::iterator end();
  LayerStack::reverse_iterator rbegin();
  LayerStack::reverse_iterator rend();

private:
  Core();
  EventQueue *eventQueue;
  EventBus *eventBus;
  LayerStack layerStack;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_CORE_H
