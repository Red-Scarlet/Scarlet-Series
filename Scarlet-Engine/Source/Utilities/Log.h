#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Scarlet {

	class Log
	{
	public:
		static void Init();
		static void Shutdown();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

}

// Core log macros
#define SCARLET_CORE_TRACE(...)		::Scarlet::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SCARLET_CORE_INFO(...)		::Scarlet::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SCARLET_CORE_WARN(...)		::Scarlet::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SCARLET_CORE_ERROR(...)		::Scarlet::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SCARLET_CORE_FATAL(...)		::Scarlet::Log::GetCoreLogger()->fatal(__VA_ARGS__)