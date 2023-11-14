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
		layer->OnDetach();
		layers.erase(it);
		layerInsertIndex--;
	}
}

void LayerStack::PopOverlay(Layer* overlay) {
	auto it = std::find(begin() + layerInsertIndex, end(), overlay);
	if (it != end()) {
		overlay->OnDetach();
		layers.erase(it);
	}
}

std::vector<Layer*>::iterator LayerStack::begin() {
	return layers.begin();
}

std::vector<Layer*>::iterator LayerStack::end() {
	return layers.end();
}

std::vector<Layer*>::reverse_iterator LayerStack::rbegin() {
	return layers.rbegin();
}

std::vector<Layer*>::reverse_iterator LayerStack::rend() {
	return layers.rend();
}

void LayerStack::MoveLayerToFront(Layer* layer) {
	auto it = std::find(layers.begin(), layers.end(), layer);
	if (it != layers.end()) {
		layers.erase(it);
		layers.insert(layers.begin() + layerInsertIndex - 1, layer);
	}
}

void LayerStack::MoveLayerToBack(Layer* layer) {
	auto it = std::find(layers.begin(), layers.end(), layer);
	if (it != layers.end()) {
		layers.erase(it);
		layers.insert(layers.begin(), layer);
		layerInsertIndex--;
	}
}