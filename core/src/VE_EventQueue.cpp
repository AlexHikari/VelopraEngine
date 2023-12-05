#include "VE_EventQueue.h"
#include "VE_Event.h"
#include "VE_LoggerMacros.h"

namespace velopraEngine {
namespace core {

// Singleton instance
EventQueue &EventQueue::Instance() {
  static EventQueue instance;
  return instance;
}

// Push a new event onto the queue
void EventQueue::PushEvent(const std::shared_ptr<Event> &event) {
  Instance().m_eventQueue.push(event);
}

// Process and dispatch all events in the queue
void EventQueue::ProcessEvents() {
  while (!Instance().m_eventQueue.empty()) {
    auto event = Instance().m_eventQueue.front();
    Instance().m_eventQueue.pop();

    VELOPRA_CORE_TRACE("Processing event: {}", event->ToString());

    auto subscribersIt = Instance().m_subscribers.find(event->GetEventType());
    if (subscribersIt != Instance().m_subscribers.end()) {
      for (auto &subscriber : subscribersIt->second) {
        subscriber->OnEvent(*event);
        if (event->Handled) {
          break;
        }
      }
    }
  }
}

// Subscribe to a specific event type
void EventQueue::Subscribe(EventType type, IEventSubscriber *subscriber) {
  Instance().m_subscribers[type].push_back(subscriber);
}

// Unsubscribe from a specific event type
void EventQueue::Unsubscribe(EventType type, IEventSubscriber *subscriber) {
  auto &subscribers = Instance().m_subscribers[type];
  subscribers.erase(
      std::remove(subscribers.begin(), subscribers.end(), subscriber),
      subscribers.end());
}

} // namespace core
} // namespace velopraEngine