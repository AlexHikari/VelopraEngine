#ifndef VE_TIME_H
#define VE_TIME_H

#include "VE_CoreAPI.h"
#include <chrono>

namespace velopraEngine {
namespace core {

class VELOPRACORE_API Time {
public:
  static Time &Instance();

  Time(Time const &) = delete;
  void operator=(Time const &) = delete;

  void Update();

  double GetDeltaTime() const;

private:
  std::chrono::high_resolution_clock::time_point lastFrameTime;
  double deltaTime;

  Time();
};

} // namespace core
} // namespace velopraEngine

#endif // VE_TIME_H