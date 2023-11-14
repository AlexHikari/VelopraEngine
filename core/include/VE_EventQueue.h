#ifndef VE_EVENT_QUEUE_H
#define VE_EVENT_QUEUE_H

#include "VE_Event.h"
#include "VE_EventSubscriber.h"
#include <queue>
#include <memory>

class EventQueue {
public:
	void PushEvent(const std::shared_ptr<Event>& event);
	void ProcessEvents();

	void Subscribe(EventSubscriber* subscriber);
	void Unsubscribe(EventSubscriber* subscriber);

private:
	std::queue<std::shared_ptr<Event>> eventQueue;
	std::vector<EventSubscriber*> subscribers;
};

#endif // VE_EVENT_QUEUE_H