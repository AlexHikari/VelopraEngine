#ifndef VE_EVENT_QUEUE_H
#define VE_EVENT_QUEUE_H

#include "VE_CoreAPI.h"
#include "VE_Event.h"
#include "VE_IEventSubscriber.h"
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

namespace velopraEngine {
namespace core {

class EventObserver;

class VELOPRACORE_API EventQueue {
public:
  static EventQueue &Instance();

  void PushEvent(const std::shared_ptr<Event> &event);
  void ProcessEvents();
  void Subscribe(EventType type, IEventSubscriber *subscriber);
  void Unsubscribe(EventType type, IEventSubscriber *subscriber);

private:
  EventQueue() = default;
  std::queue<std::shared_ptr<Event>> m_eventQueue;
  std::unordered_map<EventType, std::vector<IEventSubscriber *>> m_subscribers;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_EVENT_QUEUE_H