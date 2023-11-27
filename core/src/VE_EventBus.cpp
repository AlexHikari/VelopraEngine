#include "VE_EventBus.h"

namespace velopraEngine {
namespace core {

EventBus &EventBus::Instance() {
  static EventBus instance;
  return instance;
}

void EventBus::Subscribe(EventType type, EventCallback callback) {
  listeners[type].push_back(callback);
}

void EventBus::Unsubscribe(EventType type, EventCallback callback) {
  // Implementation to remove the callback from the vector
  // This might be a bit tricky as you can't directly compare std::function
  // objects. One approach is to use a wrapper class around std::function that
  // also stores an ID for comparison.
}

void EventBus::PostEvent(std::shared_ptr<Event> event) {
  auto &callbacks = listeners[event->GetEventType()];
  for (auto &callback : callbacks) {
    callback(event);
  }
}

} // namespace core
} // namespace velopraEngine