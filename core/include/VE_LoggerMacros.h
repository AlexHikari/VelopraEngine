#ifndef VE_LOGGER_MACROS_H
#define VE_LOGGER_MACROS_H

#include "VE_Logger.h"

// Core log macros
#define VELOPRA_CORE_TRACE(...)                                                \
  velopraEngine::core::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define VELOPRA_CORE_INFO(...)                                                 \
  velopraEngine::core::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VELOPRA_CORE_WARN(...)                                                 \
  velopraEngine::core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VELOPRA_CORE_ERROR(...)                                                \
  velopraEngine::core::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VELOPRA_CORE_CRITICAL(...)                                             \
  velopraEngine::core::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VELOPRA_TRACE(...)                                                     \
  velopraEngine::core::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define VELOPRA_INFO(...)                                                      \
  velopraEngine::core::Logger::GetClientLogger()->info(__VA_ARGS__)
#define VELOPRA_WARN(...)                                                      \
  velopraEngine::core::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define VELOPRA_ERROR(...)                                                     \
  velopraEngine::core::Logger::GetClientLogger()->error(__VA_ARGS__)
#define VELOPRA_CRITICAL(...)                                                  \
  velopraEngine::core::Logger::GetClientLogger()->critical(__VA_ARGS__)

#endif // VE_LOGGER_MACROS_H