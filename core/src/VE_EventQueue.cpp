#include "VE_EventQueue.h"
#include "VE_Event.h"
#include "VE_EventSubscriber.h"
#include "VE_LoggerMacros.h"

// Singleton instance
EventQueue& EventQueue::Instance() {
	static EventQueue instance;
	return instance;
}

// Push a new event onto the queue
void EventQueue::PushEvent(const std::shared_ptr<Event>& event) {
	Instance().eventQueue.push(event);
}

// Process and dispatch all events in the queue
void EventQueue::ProcessEvents() {
	while (!Instance().eventQueue.empty()) {
		auto event = Instance().eventQueue.front();
		Instance().eventQueue.pop();

		VELOPRA_CORE_TRACE("Processing event: {}", event->ToString());

		auto subscribersIt = Instance().subscribers.find(event->GetEventType());
		if (subscribersIt != Instance().subscribers.end()) {
			for (auto& subscriber : subscribersIt->second) {
				subscriber->OnEvent(*event);
				if (event->Handled) {
					break;
				}
			}
		}
	}
}

// Subscribe to a specific event type
void EventQueue::Subscribe(EventType type, EventSubscriber* subscriber) {
	Instance().subscribers[type].push_back(subscriber);
}

// Unsubscribe from a specific event type
void EventQueue::Unsubscribe(EventType type, EventSubscriber* subscriber) {
	auto& subscribers = Instance().subscribers[type];
	subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}
