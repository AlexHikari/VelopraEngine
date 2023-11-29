#ifndef VE_IMESH_H
#define VE_IMESH_H

#include "VE_Math.h"
#include <vector>

namespace velopraEngine {
namespace render {

struct Vertex {
  core::Vector3 position;
  core::Vector3 normal;
  core::Vector2 texCoords;
};

class IMesh {
public:
  virtual ~IMesh() = default;
  virtual void Draw() const = 0;
};

} // namespace render
} // namespace velopraEngine

#endif // VE_IMESH_H
