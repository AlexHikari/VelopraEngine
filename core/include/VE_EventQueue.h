#ifndef VE_EVENT_QUEUE_H
#define VE_EVENT_QUEUE_H

#include "VE_Event.h"
#include <queue>
#include <memory>
#include <unordered_map>
#include <vector>

class EventSubscriber;

class EventQueue {
public:
	static EventQueue& Instance();

	void PushEvent(const std::shared_ptr<Event>& event);
	void ProcessEvents();
	void Subscribe(EventType type, EventSubscriber* subscriber);
	void Unsubscribe(EventType type, EventSubscriber* subscriber);

private:
	EventQueue() = default;
	std::queue<std::shared_ptr<Event>> eventQueue;
	std::unordered_map<EventType, std::vector<EventSubscriber*>> subscribers;
};

#endif // VE_EVENT_QUEUE_H