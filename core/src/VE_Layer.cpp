#include "VE_Layer.h"

Layer::Layer(const std::string& name, const std::unordered_set<EventType>& initialEvents) 
    : name(name), isVisible(true), interestedEvents(initialEvents) {
}

void Layer::SetInterestedEvents(const std::unordered_set<EventType>& events) {
    interestedEvents = events;
}

const std::string& Layer::GetName() const {
	return name;
}

void Layer::SetVisible(bool visible) {
	isVisible = visible;
}

bool Layer::IsVisible() const {
	return isVisible;
}

void Layer::HandleEvent(Event& event) {
	if (interestedEvents.find(event.GetEventType()) != interestedEvents.end()) {
		OnEvent(event);
	}
}

