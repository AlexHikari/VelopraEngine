#ifndef VE_EVENTBUS_H
#define VE_EVENTBUS_H

#include "VE_Event.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

class EventBus {
public:
	using EventCallback = std::function<void(std::shared_ptr<Event>)>;

	static EventBus& Instance();

	EventBus(const EventBus&) = delete;
	EventBus& operator=(const EventBus&) = delete;

	void Subscribe(EventType type, EventCallback callback);
	void Unsubscribe(EventType type, EventCallback callback);
	void PostEvent(std::shared_ptr<Event> event);

private:
	EventBus() = default;

	std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};

#endif // VE_EVENTBUS_H