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

Matrix4 Matrix4::Perspective(float32 fovDegrees, float32 aspectRatio,
                           float32 nearPlane, float32 farPlane) {
  Matrix4 result = {}; // Initialize to zero
  const float32 fovRadians = static_cast<float32>(fovDegrees * (M_PI / 180.0f));
  const float32 tanHalfFov = std::tan(fovRadians / 2.0f);

  result.m[0][0] = 1.0f / (aspectRatio * tanHalfFov);
  result.m[1][1] = 1.0f / tanHalfFov;
  result.m[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
  result.m[2][3] = -1.0f;
  result.m[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

  return result;
}
Matrix4 Matrix4::Orthographic(float32 left, float32 right, float32 bottom,
                            float32 top, float32 nearPlane, float32 farPlane) {
  Matrix4 result = {}; // Initialize to zero

  result.m[0][0] = 2.0f / (right - left);
  result.m[1][1] = 2.0f / (top - bottom);
  result.m[2][2] = -2.0f / (farPlane - nearPlane);
  result.m[3][0] = -(right + left) / (right - left);
  result.m[3][1] = -(top + bottom) / (top - bottom);
  result.m[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
  result.m[3][3] = 1.0f;

  return result;
}

Quaternion::Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
Quaternion::Quaternion(float32 w, float32 x, float32 y, float32 z)
    : w(w), x(x), y(y), z(z) {}

// Quaternion multiplication
Quaternion Quaternion::operator*(const Quaternion &rhs) const {
  return Quaternion(w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z,
                    w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                    w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
                    w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w);
}

// Normalize the quaternion
void Quaternion::Normalize() {
  float32 norm = std::sqrt(w * w + x * x + y * y + z * z);
  if (norm > 0.0f) {
    float32 invNorm = 1.0f / norm;
    w *= invNorm;
    x *= invNorm;
    y *= invNorm;
    z *= invNorm;
  }
}

// Static function to create a quaternion from Euler angles (in degrees)
Quaternion Quaternion::FromEulerAngles(float32 pitch, float32 yaw,
                                       float32 roll) {
  pitch = static_cast<float32>(pitch * M_PI / 180.0f);
  yaw = static_cast<float32>(yaw * M_PI / 180.0f);
  roll = static_cast<float32>(roll * M_PI / 180.0f);

  float32 cy = cos(yaw * 0.5f);
  float32 sy = sin(yaw * 0.5f);
  float32 cp = cos(pitch * 0.5f);
  float32 sp = sin(pitch * 0.5f);
  float32 cr = cos(roll * 0.5f);
  float32 sr = sin(roll * 0.5f);

  return Quaternion(cr * cp * cy + sr * sp * sy, sr * cp * cy - cr * sp * sy,
                    cr * sp * cy + sr * cp * sy, cr * cp * sy - sr * sp * cy);
}

} // namespace core
} // namespace velopraEngine