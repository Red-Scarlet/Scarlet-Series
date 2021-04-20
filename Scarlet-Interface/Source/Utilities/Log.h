#pragma once

#include "Core/Common.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ScarletInterface {

	class Log
	{
	public:
		static void Init();
		static void Shutdown();
		inline static std::shared_ptr<spdlog::logger>& GetInterfaceLogger() { return s_InterfaceLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_InterfaceLogger;
	};

}

// Core log macros
#define SCARLET_INTERFACE_TRACE(...)		::ScarletInterface::Log::GetInterfaceLogger()->trace(__VA_ARGS__)
#define SCARLET_INTERFACE_INFO(...)			::ScarletInterface::Log::GetInterfaceLogger()->info(__VA_ARGS__)
#define SCARLET_INTERFACE_WARN(...)			::ScarletInterface::Log::GetInterfaceLogger()->warn(__VA_ARGS__)
#define SCARLET_INTERFACE_ERROR(...)		::ScarletInterface::Log::GetInterfaceLogger()->error(__VA_ARGS__)
#define SCARLET_INTERFACE_FATAL(...)		::ScarletInterface::Log::GetInterfaceLogger()->fatal(__VA_ARGS__)