#ifndef VE_IMESH_H
#define VE_IMESH_H

#include "VE_Math.h"
#include <vector>

struct Vertex {
  VelopraEngine::Core::Vector3 position;
  VelopraEngine::Core::Vector3 normal;
  VelopraEngine::Core::Vector2 texCoords;
};

class IMesh {
public:
  virtual ~IMesh() = default;
  virtual void Draw() const = 0;
};

#endif // VE_IMESH_H
