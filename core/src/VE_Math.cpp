#include "VE_Math.h"

namespace velopraEngine {
namespace core {

Vector2::Vector2() : x(0.0f), y(0.0f) {}
Vector2::Vector2(float32 x, float32 y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2 &rhs) const {
  return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &rhs) const {
  return Vector2(x - rhs.x, y - rhs.y);
}

float32 Vector3::Magnitude(const Vector3 &vec) {
  return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vector3 Vector3::Normalize(const Vector3 &vec) {
  float32 mag = Magnitude(vec);
  if (mag > 0.0f) {
    return vec / mag;
  } else {
    VELOPRA_CORE_ERROR("Attempted to normalize a zero vector.");
    return Vector3(0.0f, 0.0f, 0.0f);
  }
}

Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs) {
  return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                 lhs.x * rhs.y - lhs.y * rhs.x);
}

float32 Vector3::Distance(const Vector3 &a, const Vector3 &b) {
  return Magnitude(a - b);
}

Vector3 Vector3::Lerp(const Vector3 &start, const Vector3 &end, float32 t) {
  return (1 - t) * start + t * end;
}

Matrix4::Matrix4() {
  // Initialize to identity matrix
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      m[i][j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}
} // namespace core
} // namespace velopraEngine