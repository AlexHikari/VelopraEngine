#ifndef VE_MOUSE_EVENT_H
#define VE_MOUSE_EVENT_H

#include "VE_Event.h"

class MouseMovedEvent : public Event {
public:
	MouseMovedEvent(float x, float y)
		: MouseX(x), MouseY(y) {}

	EventType GetEventType() const override { return EventType::MouseMoved; }
	const char* GetName() const override { return "MouseMoved"; }

	float MouseX, MouseY;
};

class MouseButtonReleasedEvent : public Event {
public:
	MouseButtonReleasedEvent(int button)
		: Button(button) {}

	EventType GetEventType() const override { return EventType::MouseButtonReleased; }
	const char* GetName() const override { return "MouseButtonReleased"; }

	int Button;
};

class MouseButtonPressedEvent : public Event {
public:
	MouseButtonPressedEvent(int button)
		: Button(button) {}

	EventType GetEventType() const override { return EventType::MouseButtonPressed; }
	const char* GetName() const override { return "MouseButtonPressed"; }

	int Button;
};

#endif // VE_MOUSE_EVENT_H