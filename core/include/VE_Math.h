#ifndef VE_CORE_MATH_H
#define VE_CORE_MATH_H

#include "VE_CoreAPI.h"
#include "VE_Types.h"
#include "VE_LoggerMacros.h"

#include <cmath>

// Define M_PI in case it's not included in <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace velopraEngine {
namespace core {

struct VELOPRACORE_API Vector2 {
  float32 x, y;

  Vector2();
  Vector2(float32 x, float32 y);

  Vector2 operator+(const Vector2 &rhs) const;

  Vector2 operator-(const Vector2 &rhs) const;

  inline float32 Dot(const Vector2 &lhs, const Vector2 &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
};

struct VELOPRACORE_API Vector3 {
  float32 x, y, z;

  Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
  Vector3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {}

  Vector3 operator+(const Vector3 &rhs) const {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  Vector3 operator-(const Vector3 &rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  Vector3 operator/(float32 scalar) const {
    if (scalar == 0.0f) {
      VELOPRA_CORE_ERROR("Attempted to divide Vector3 by zero.");
      return Vector3(0.0f, 0.0f, 0.0f); // Return a zero vector
    }
    return Vector3(x / scalar, y / scalar, z / scalar);
  }

  Vector3 operator*(float32 scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
  }

  static float32 Magnitude(const Vector3 &vec);
  static Vector3 Normalize(const Vector3 &vec);
  static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs);
  static float32 Distance(const Vector3 &a, const Vector3 &b);
  static Vector3 Lerp(const Vector3 &start, const Vector3 &end, float32 t);

  friend Vector3 operator*(float32 scalar, const Vector3 &vec) {
    return vec * scalar;
  }
};

struct VELOPRACORE_API Matrix4 {
  float32 m[4][4];

  Matrix4();

  inline Matrix4 Multiply(const Matrix4 &lhs, const Matrix4 &rhs) {
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        result.m[i][j] = 0.0f;
        for (int k = 0; k < 4; ++k) {
          result.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
        }
      }
    }
    return result;
  }
  inline Matrix4 Transpose(const Matrix4 &matrix) {
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        result.m[j][i] = matrix.m[i][j];
      }
    }
    return result;
  }
  inline Matrix4 Scale(const Vector3 &scaleFactors) {
    Matrix4 result;
    result.m[0][0] = scaleFactors.x;
    result.m[1][1] = scaleFactors.y;
    result.m[2][2] = scaleFactors.z;
    return result;
  }

  inline Matrix4 Translate(const Vector3 &translation) {
    Matrix4 result;
    result.m[3][0] = translation.x;
    result.m[3][1] = translation.y;
    result.m[3][2] = translation.z;
    return result;
  }

  inline Matrix4 Rotate(float32 angle, const Vector3 &axis) {
    Matrix4 rotationMatrix;
    const float32 radians =
        static_cast<float32>(angle * M_PI / 180.0f); // Convert to radians
    const float32 cosTheta = std::cos(radians);
    const float32 sinTheta = std::sin(radians);
    const Vector3 normalizedAxis = Vector3::Normalize(axis);

    rotationMatrix.m[0][0] =
        cosTheta + normalizedAxis.x * normalizedAxis.x * (1 - cosTheta);
    rotationMatrix.m[0][1] =
        normalizedAxis.x * normalizedAxis.y * (1 - cosTheta) -
        normalizedAxis.z * sinTheta;
    rotationMatrix.m[0][2] =
        normalizedAxis.x * normalizedAxis.z * (1 - cosTheta) +
        normalizedAxis.y * sinTheta;

    rotationMatrix.m[1][0] =
        normalizedAxis.y * normalizedAxis.x * (1 - cosTheta) +
        normalizedAxis.z * sinTheta;
    rotationMatrix.m[1][1] =
        cosTheta + normalizedAxis.y * normalizedAxis.y * (1 - cosTheta);
    rotationMatrix.m[1][2] =
        normalizedAxis.y * normalizedAxis.z * (1 - cosTheta) -
        normalizedAxis.x * sinTheta;

    rotationMatrix.m[2][0] =
        normalizedAxis.z * normalizedAxis.x * (1 - cosTheta) -
        normalizedAxis.y * sinTheta;
    rotationMatrix.m[2][1] =
        normalizedAxis.z * normalizedAxis.y * (1 - cosTheta) +
        normalizedAxis.x * sinTheta;
    rotationMatrix.m[2][2] =
        cosTheta + normalizedAxis.z * normalizedAxis.z * (1 - cosTheta);

    // The last row and column are for affine transformations. Since this is a
    // pure rotation, we set them to represent no translation and no perspective
    // distortion.
    rotationMatrix.m[3][0] = 0.0f;
    rotationMatrix.m[3][1] = 0.0f;
    rotationMatrix.m[3][2] = 0.0f;
    rotationMatrix.m[0][3] = 0.0f;
    rotationMatrix.m[1][3] = 0.0f;
    rotationMatrix.m[2][3] = 0.0f;
    rotationMatrix.m[3][3] = 1.0f;

    return rotationMatrix;
  }
  inline Matrix4 Perspective(float32 fovDegrees, float32 aspectRatio,
                             float32 nearPlane, float32 farPlane) {
    Matrix4 result = {}; // Initialize to zero
    const float32 fovRadians =
        static_cast<float32>(fovDegrees * (M_PI / 180.0f));
    const float32 tanHalfFov = std::tan(fovRadians / 2.0f);

    result.m[0][0] = 1.0f / (aspectRatio * tanHalfFov);
    result.m[1][1] = 1.0f / tanHalfFov;
    result.m[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    result.m[2][3] = -1.0f;
    result.m[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

    return result;
  }
  inline Matrix4 Orthographic(float32 left, float32 right, float32 bottom,
                              float32 top, float32 nearPlane,
                              float32 farPlane) {
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
};

} // namespace core
} // namespace velopraEngine

#endif // VE_CORE_MATH_H