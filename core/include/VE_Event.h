#ifndef VE_EVENT_H
#define VE_EVENT_H

#include "VE_CoreAPI.h"
#include <string>


namespace velopraEngine {
namespace core {

enum class VELOPRACORE_API EventType {
  None = 0,
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowLostFocus,
  WindowMoved,
  KeyPressed,
  KeyReleased,
  MouseButtonPressed,
  MouseButtonReleased,
  MouseMoved,
  MouseScrolled
};

class VELOPRACORE_API Event {
public:
  virtual ~Event() = default;

  virtual EventType GetEventType() const = 0;
  virtual const char *GetName() const = 0;
  virtual std::string ToString() const;

  bool Handled = false;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_EVENT_H