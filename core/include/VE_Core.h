#ifndef VE_CORE_H
#define VE_CORE_H

#include "VE_EventQueue.h"
#include "VE_Layer.h"
#include "VE_LayerStack.h"

class Core {
public:
	static Core& Instance();
	EventQueue& GetEventQueue();

	Core(Core const&) = delete;
	void operator=(Core const&) = delete;

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

	LayerStack::iterator begin();
	LayerStack::iterator end();
	LayerStack::reverse_iterator rbegin();
	LayerStack::reverse_iterator rend();

private:
	Core() = default;
	EventQueue eventQueue;
	LayerStack layerStack;
};

#endif // VE_CORE_H
