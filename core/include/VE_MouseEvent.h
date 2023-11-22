#ifndef VE_MOUSE_EVENT_H
#define VE_MOUSE_EVENT_H

#include "VE_CoreAPI.h"
#include "VE_Event.h"

namespace velopraEngine {
namespace core {

class VELOPRACORE_API MouseMovedEvent : public Event {
public:
  MouseMovedEvent(float x, float y);

  EventType GetEventType() const override;
  const char *GetName() const override;

  float MouseX, MouseY;
};

class VELOPRACORE_API MouseButtonReleasedEvent : public Event {
public:
  MouseButtonReleasedEvent(int button);

  EventType GetEventType() const override;
  const char *GetName() const override;

  int Button;
};

class VELOPRACORE_API MouseButtonPressedEvent : public Event {
public:
  MouseButtonPressedEvent(int button);

  EventType GetEventType() const override;
  const char *GetName() const override;

  int Button;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_MOUSE_EVENT_H