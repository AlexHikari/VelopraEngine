#include "VE_Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

void Logger::Init() {
			// Initialize spdlog's async logging feature (creates a thread pool)
			spdlog::init_thread_pool(8192, 1); // Queue size and number of threads

			// Create the asynchronous color multi-threaded loggers
			auto core_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			s_CoreLogger = std::make_shared<spdlog::async_logger>("VELOPRA_CORE", core_sink, spdlog::thread_pool());
			s_CoreLogger->set_level(spdlog::level::trace);
			s_CoreLogger->flush_on(spdlog::level::err);

			auto client_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			s_ClientLogger = std::make_shared<spdlog::async_logger>("VELOPRA_APP", client_sink, spdlog::thread_pool());
			s_ClientLogger->set_level(spdlog::level::trace);
			s_ClientLogger->flush_on(spdlog::level::err);

			spdlog::set_pattern("%^[%T] %n: %v%$"); // Set the pattern for the logging output
}
