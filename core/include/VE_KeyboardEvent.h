#ifndef VE_KEYBOARD_EVENT_H
#define VE_KEYBOARD_EVENT_H

#include "VE_Event.h"

class KeyPressedEvent : public Event {
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyCode(keycode), RepeatCount(repeatCount) {}

	EventType GetEventType() const override { return EventType::KeyPressed; }
	const char* GetName() const override { return "KeyPressed"; }

	int KeyCode, RepeatCount;
};

class KeyReleasedEvent : public Event {
public:
	KeyReleasedEvent(int keycode)
		: KeyCode(keycode) {}

	EventType GetEventType() const override { return EventType::KeyReleased; }
	const char* GetName() const override { return "KeyReleased"; }

	int KeyCode;
};


#endif // VE_KEYBOARD_EVENT_H