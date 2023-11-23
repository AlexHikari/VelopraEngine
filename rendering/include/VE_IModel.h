#ifndef VE_IMODEL_H
#define VE_IMODEL_H

#include "VE_ITransform.h"

namespace velopraEngine {
namespace render {

class IModel {
public:
  virtual ~IModel() = default;
  virtual void Draw() const = 0;
  virtual void SetTransform(const ITransform &transform) = 0;
  virtual ITransform &GetTransform() = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_IMODEL_H