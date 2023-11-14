#ifndef VE_EVENT_SUBSCRIBER_H
#define VE_EVENT_SUBSCRIBER_H

#include "VE_Event.h"

class EventSubscriber {
public:
	virtual ~EventSubscriber() = default;
	virtual void OnEvent(const Event& event) = 0;
};

#endif // VE_EVENT_SUBSCRIBER_H
