#ifndef VE_KEYBOARD_EVENT_H
#define VE_KEYBOARD_EVENT_H

#include "VE_CoreAPI.h"
#include "VE_Event.h"

namespace velopraEngine {
namespace core {

class VELOPRACORE_API KeyPressedEvent : public Event {
public:
  KeyPressedEvent(int keycode, int repeatCount);

  EventType GetEventType() const override;
  const char *GetName() const override;

  int KeyCode, RepeatCount;
};

class VELOPRACORE_API KeyReleasedEvent : public Event {
public:
  KeyReleasedEvent(int keycode);

  EventType GetEventType() const override;
  const char *GetName() const override;

  int KeyCode;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_KEYBOARD_EVENT_H