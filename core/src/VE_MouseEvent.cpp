#include "VE_MouseEvent.h"

namespace velopraEngine {
namespace core {

MouseMovedEvent::MouseMovedEvent(float x, float y) : MouseX(x), MouseY(y) {}

EventType MouseMovedEvent::GetEventType() const {
  return EventType::MouseMoved;
}
const char *MouseMovedEvent::GetName() const { return "MouseMoved"; }

MouseButtonReleasedEvent::MouseButtonReleasedEvent(int button)
    : Button(button) {}

EventType MouseButtonReleasedEvent::GetEventType() const {
  return EventType::MouseButtonReleased;
}
const char *MouseButtonReleasedEvent::GetName() const {
  return "MouseButtonReleased";
}

MouseButtonPressedEvent::MouseButtonPressedEvent(int button) : Button(button) {}

EventType MouseButtonPressedEvent::GetEventType() const {
  return EventType::MouseButtonPressed;
}
const char *MouseButtonPressedEvent::GetName() const {
  return "MouseButtonPressed";
}

} // namespace core
} // namespace velopraEngine