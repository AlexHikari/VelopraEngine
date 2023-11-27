#ifndef VE_EVENT_QUEUE_H
#define VE_EVENT_QUEUE_H

#include "VE_Event.h"
#include "VE_CoreAPI.h"
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

namespace velopraEngine {
namespace core {

class EventSubscriber;

class VELOPRACORE_API EventQueue {
public:
  static EventQueue &Instance();

  void PushEvent(const std::shared_ptr<Event> &event);
  void ProcessEvents();
  void Subscribe(EventType type, EventSubscriber *subscriber);
  void Unsubscribe(EventType type, EventSubscriber *subscriber);

private:
  EventQueue() = default;
  std::queue<std::shared_ptr<Event>> eventQueue;
  std::unordered_map<EventType, std::vector<EventSubscriber *>> subscribers;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_EVENT_QUEUE_H