#ifndef VE_LAYER_STACK_H
#define VE_LAYER_STACK_H

#include "VE_Layer.h"
#include <vector>

class LayerStack {
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* overlay);

	typedef std::vector<Layer*>::iterator iterator;
	typedef std::vector<Layer*>::reverse_iterator reverse_iterator;

	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

private:
	std::vector<Layer*> layers;
	unsigned int layerInsertIndex;
};

#endif // VE_LAYER_STACK_H