#ifndef VE_KEYBOARD_EVENT_H
#define VE_KEYBOARD_EVENT_H

#include "Event.h"

class KeyPressedEvent : public Event {
public:
	KeyPressedEvent(int keycode, int repeatCount)
		: KeyCode(keycode), RepeatCount(repeatCount) {}

	EventType GetEventType() const override { return EventType::KeyPressed; }
	const char* GetName() const override { return "KeyPressed"; }

	int KeyCode, RepeatCount;
};


#endif // VE_KEYBOARD_EVENT_H