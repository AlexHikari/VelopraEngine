#ifndef VE_EVENTBUS_H
#define VE_EVENTBUS_H

#include "VE_CoreAPI.h"
#include "VE_Event.h"
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace velopraEngine {
namespace core {

class VELOPRACORE_API EventBus {
public:
  using EventCallback = std::function<void(std::shared_ptr<Event>)>;

  static EventBus &Instance();

  EventBus(const EventBus &) = delete;
  EventBus &operator=(const EventBus &) = delete;

  void Subscribe(EventType type, EventCallback callback);
  void Unsubscribe(EventType type, EventCallback callback);
  void PostEvent(std::shared_ptr<Event> event);

private:
  EventBus() = default;

  std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_EVENTBUS_H