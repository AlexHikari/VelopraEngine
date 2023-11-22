#ifndef VE_EVENT_SUBSCRIBER_H
#define VE_EVENT_SUBSCRIBER_H

#include "VE_CoreAPI.h"
#include "VE_Event.h"

namespace velopraEngine {
namespace core {

class VELOPRACORE_API EventSubscriber {
public:
  virtual ~EventSubscriber() = default;
  virtual void OnEvent(const Event &event) = 0;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_EVENT_SUBSCRIBER_H
