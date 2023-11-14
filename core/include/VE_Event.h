#ifndef VE_EVENT_H
#define VE_EVENT_H

#include <string>

enum class EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	// Add more event types as needed
};

class Event {
public:
	virtual ~Event() = default;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool Handled = false;
};

#endif // VE_EVENT_H