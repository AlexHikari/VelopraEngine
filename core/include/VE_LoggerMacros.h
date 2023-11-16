#ifndef VE_LOGGER_MACROS_H
#define VE_LOGGER_MACROS_H

#include "VE_Logger.h"

// Core log macros
#define VELOPRA_CORE_TRACE(...)   ::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define VELOPRA_CORE_INFO(...)    ::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VELOPRA_CORE_WARN(...)    ::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VELOPRA_CORE_ERROR(...)   ::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VELOPRA_CORE_CRITICAL(...) ::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VELOPRA_TRACE(...)        ::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define VELOPRA_INFO(...)         ::Logger::GetClientLogger()->info(__VA_ARGS__)
#define VELOPRA_WARN(...)         ::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define VELOPRA_ERROR(...)        ::Logger::GetClientLogger()->error(__VA_ARGS__)
#define VELOPRA_CRITICAL(...)     ::Logger::GetClientLogger()->critical(__VA_ARGS__)

#endif // VE_LOGGER_MACROS_H