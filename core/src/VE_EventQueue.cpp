#include "VE_EventQueue.h"
#include "VE_Core.h"

void EventQueue::PushEvent(const std::shared_ptr<Event>& event) {
	eventQueue.push(event);
}

void EventQueue::Subscribe(EventSubscriber* subscriber) {
	subscribers.push_back(subscriber);
}

void EventQueue::Unsubscribe(EventSubscriber* subscriber) {
	subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void EventQueue::ProcessEvents() {
	Core& coreInstance = Core::Instance();

	while (!eventQueue.empty()) {
		auto event = eventQueue.front();
		eventQueue.pop();

		for (auto it = coreInstance.rbegin(); it != coreInstance.rend(); ++it) {
			if ((*it)->IsVisible()) {
				(*it)->HandleEvent(*event);
				if (event->Handled) {
					break;
				}
			}
		}
	}
}