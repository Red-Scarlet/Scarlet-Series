#include "Log.h"

namespace ScarletInterface {

	std::shared_ptr<spdlog::logger> Log::s_InterfaceLogger;
	
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
	
		s_InterfaceLogger = spdlog::stdout_color_mt("Interface");
		s_InterfaceLogger->set_level(spdlog::level::trace);
	}
	
	void Log::Shutdown()
	{
		spdlog::shutdown();
	}

}