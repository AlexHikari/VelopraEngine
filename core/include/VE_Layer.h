#ifndef VE_LAYER_H
#define VE_LAYER_H

#include "VE_CoreAPI.h"
#include <string>

namespace velopraEngine {
namespace core {

class VELOPRACORE_API Layer {
public:
  Layer(const std::string &name);
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}

  const std::string &GetName() const;
  void SetVisible(bool visible);
  bool IsVisible() const;

protected:
  std::string name;
  bool isVisible;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_LAYER_H