#ifndef VE_CORE_LOGGER_H
#define VE_CORE_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace VelopraEngine {
	namespace Core {

		class Logger {
		public:
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		private:
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
		};

	} // namespace Core
} // namespace VelopraEngine

// Core log macros
#define VELOPRA_CORE_TRACE(...)   ::VelopraEngine::Core::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define VELOPRA_CORE_INFO(...)    ::VelopraEngine::Core::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define VELOPRA_CORE_WARN(...)    ::VelopraEngine::Core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define VELOPRA_CORE_ERROR(...)   ::VelopraEngine::Core::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define VELOPRA_CORE_CRITICAL(...) ::VelopraEngine::Core::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VELOPRA_TRACE(...)        ::VelopraEngine::Core::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define VELOPRA_INFO(...)         ::VelopraEngine::Core::Logger::GetClientLogger()->info(__VA_ARGS__)
#define VELOPRA_WARN(...)         ::VelopraEngine::Core::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define VELOPRA_ERROR(...)        ::VelopraEngine::Core::Logger::GetClientLogger()->error(__VA_ARGS__)
#define VELOPRA_CRITICAL(...)     ::VelopraEngine::Core::Logger::GetClientLogger()->critical(__VA_ARGS__)

#endif // VE_CORE_LOGGER_H
