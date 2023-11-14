#ifndef VE_MOUSE_EVENT_H
#define VE_MOUSE_EVENT_H

#include "Event.h"

class MouseMovedEvent : public Event {
public:
	MouseMovedEvent(float x, float y)
		: MouseX(x), MouseY(y) {}

	EventType GetEventType() const override { return EventType::MouseMoved; }
	const char* GetName() const override { return "MouseMoved"; }

	float MouseX, MouseY;
};

#endif // VE_MOUSE_EVENT_H