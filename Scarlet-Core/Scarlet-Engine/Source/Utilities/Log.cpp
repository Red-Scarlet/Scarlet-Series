#include "Scarletpch.h"
#include "Log.h"

namespace Scarlet {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
	
		s_CoreLogger = spdlog::stdout_color_mt("Scarlet");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
	
	void Log::Shutdown()
	{
		spdlog::shutdown();
	}

}