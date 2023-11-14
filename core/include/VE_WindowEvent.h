#ifndef VE_WINDOW_EVENT_H
#define VE_WINDOW_EVENT_H

#include "Event.h"

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
		: Width(width), Height(height) {}

	EventType GetEventType() const override { return EventType::WindowResize; }
	const char* GetName() const override { return "WindowResize"; }

	unsigned int Width, Height;
};

#endif //VE_WINDOW_EVENT_H