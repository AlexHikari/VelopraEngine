#include "VE_KeyboardEvent.h"

namespace velopraEngine {
namespace core {

KeyPressedEvent::KeyPressedEvent(int keycode, int repeatCount)
    : KeyCode(keycode), RepeatCount(repeatCount) {}

EventType KeyPressedEvent::GetEventType() const {
  return EventType::KeyPressed;
}
const char *KeyPressedEvent::GetName() const { return "KeyPressed"; }

KeyReleasedEvent::KeyReleasedEvent(int keycode) : KeyCode(keycode) {}

EventType KeyReleasedEvent::GetEventType() const {
  return EventType::KeyReleased;
}
const char *KeyReleasedEvent::GetName() const { return "KeyReleased"; }

} // namespace core
} // namespace velopraEngine