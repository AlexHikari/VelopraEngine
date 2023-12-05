#ifndef VE_WINDOW_EVENT_H
#define VE_WINDOW_EVENT_H

#include "VE_CoreAPI.h"
#include "VE_Event.h"

namespace velopraEngine {
namespace core {

class VELOPRACORE_API WindowResizeEvent : public Event {
public:
  WindowResizeEvent(unsigned int width, unsigned int height);

  EventType GetEventType() const override;
  const char *GetName() const override;

  unsigned int Width, Height;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_WINDOW_EVENT_H