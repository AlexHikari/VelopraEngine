#ifndef VE_CORE_LOGGER_H
#define VE_CORE_LOGGER_H

#include "VE_CoreAPI.h"
#include <memory>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>


namespace velopraEngine {
namespace core {

class VELOPRACORE_API Logger {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return s_ClientLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

} // namespace core
} // namespace velopraEngine

#endif // VE_CORE_LOGGER_H
