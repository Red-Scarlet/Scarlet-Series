#include "Scarletpch.h"
#include "Application.h"
#include "Utilities/Timestep.h"

namespace Scarlet {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application(const String& _ApplicationTitle)
		: m_Title(_ApplicationTitle), m_LastFrameTime(0.00f)
	{
		SCARLET_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
	}

	void Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			float32 time = 0.00f;
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_InterfaceController.OnUpdate();
		}

		m_Running = false;
	}

	void Application::Stop()
	{
		m_Running = false;
	}

}