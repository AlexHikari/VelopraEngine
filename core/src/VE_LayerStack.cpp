#include "VE_LayerStack.h"
#include <algorithm>

LayerStack::LayerStack() : layerInsertIndex(0) {}

LayerStack::~LayerStack() {
	for (Layer* layer : layers) {
		delete layer;
	}
}

void LayerStack::PushLayer(Layer* layer) {
	layers.emplace(layers.begin() + layerInsertIndex, layer);
	layerInsertIndex++;
}

void LayerStack::PushOverlay(Layer* overlay) {
	layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer* layer) {
	auto it = std::find(begin(), begin() + layerInsertIndex, layer);
	if (it != begin() + layerInsertIndex) {
		layers.erase(it);
		layerInsertIndex--;
	}
}

void LayerStack::PopOverlay(Layer* overlay) {
	auto it = std::find(begin() + layerInsertIndex, end(), overlay);
	if (it != end()) {
		layers.erase(it);
	}
}

LayerStack::iterator LayerStack::begin() {
	return layers.begin();
}

LayerStack::iterator LayerStack::end() {
	return layers.end();
}

LayerStack::reverse_iterator LayerStack::rbegin() {
	return layers.rbegin();
}

LayerStack::reverse_iterator LayerStack::rend() {
	return layers.rend();
}
