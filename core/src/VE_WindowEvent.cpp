#include "VE_WindowEvent.h"

namespace velopraEngine {
namespace core {

WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
    : Width(width), Height(height) {}

EventType WindowResizeEvent::GetEventType() const {
  return EventType::WindowResize;
}
const char *WindowResizeEvent::GetName() const { return "WindowResize"; }

} // namespace core
} // namespace velopraEngine
