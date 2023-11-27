#ifndef VE_TIME_H
#define VE_TIME_H

#include "VE_CoreAPI.h"
#include <chrono>

namespace velopraEngine {
namespace core {

class VELOPRACORE_API Time {
private:
  std::chrono::high_resolution_clock::time_point lastFrameTime;
  double deltaTime;

  Time() : deltaTime(0.0) {
    lastFrameTime = std::chrono::high_resolution_clock::now();
  }

public:
  // Singleton instance
  static Time &Instance() {
    static Time instance;
    return instance;
  }

  Time(Time const &) = delete;
  void operator=(Time const &) = delete;

  void Update() {
    auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<double, std::chrono::seconds::period>(
                    now - lastFrameTime)
                    .count();
    lastFrameTime = now;
  }

  double GetDeltaTime() const { return deltaTime; }

  // Additional methods can be added here
};

} // namespace core
} // namespace velopraEngine

#endif