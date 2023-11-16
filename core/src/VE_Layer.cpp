#include "VE_Layer.h"

Layer::Layer(const std::string& name)
	: name(name), isVisible(true) {}

const std::string& Layer::GetName() const {
	return name;
}

void Layer::SetVisible(bool visible) {
	isVisible = visible;
}

bool Layer::IsVisible() const {
	return isVisible;
}