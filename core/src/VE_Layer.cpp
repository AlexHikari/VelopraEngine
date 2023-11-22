#include "VE_Layer.h"

namespace velopraEngine {
namespace core {

Layer::Layer(const std::string &name) : name(name), isVisible(true) {}

const std::string &Layer::GetName() const { return name; }

void Layer::SetVisible(bool visible) { isVisible = visible; }

bool Layer::IsVisible() const { return isVisible; }

} // namespace core
} // namespace velopraEngine