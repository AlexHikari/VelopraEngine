#include "VE_Time.h"

namespace velopraEngine {
namespace core {

Time::Time() : deltaTime(0.0) {
  lastFrameTime = std::chrono::high_resolution_clock::now();
}

void Time::Update() {
  auto now = std::chrono::high_resolution_clock::now();
  deltaTime = std::chrono::duration<double, std::chrono::seconds::period>(
                  now - lastFrameTime)
                  .count();
  lastFrameTime = now;
}

Time &Time::Instance() {
  static Time instance;
  return instance;
}

double Time::GetDeltaTime() const { return deltaTime; }

} // namespace core
} // namespace velopraEngine