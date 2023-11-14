#ifndef VE_LAYER_H
#define VE_LAYER_H

#include "VE_Event.h"
#include <string>
#include <unordered_set>

class Event;
enum class EventType;

class Layer {
public:
	Layer(const std::string& name, const std::unordered_set<EventType>& initialEvents = {});
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnEvent(Event& event) {}

	const std::string& GetName() const;
	void SetVisible(bool visible);
	bool IsVisible() const;

	virtual void HandleEvent(Event& event);

	void SetInterestedEvents(const std::unordered_set<EventType>& events);

protected:
	std::string name;
	bool isVisible;
	std::unordered_set<EventType> interestedEvents;
};

#endif // VE_LAYER_H