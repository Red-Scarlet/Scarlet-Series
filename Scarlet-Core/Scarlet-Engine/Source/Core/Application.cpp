#include "Scarletpch.h"
#include "Application.h"
#include "Utilities/FileUtils.h"
#include <filesystem>

#include <UI/PanelUI.h>

namespace Scarlet {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application(const String& _ApplicationTitle)
		: m_Title(_ApplicationTitle), m_LastFrameTime(0.00f)
	{
		SCARLET_PROFILE_FUNCTION();

		SCARLET_CORE_ASSERT(!s_Instance, "Application already exists!");
		this->s_Instance = this;
		this->m_EventCallback = SCARLET_BIND_EVENT_FN(Application::OnEvent);
		m_ModuleManager = CreateRef<ModuleManager>();
		m_NumThreads = std::thread::hardware_concurrency() - 1;
		m_Running = true;

		// Todo: Change to unique system to identify if module has been dropped.
		if (!FileUtils::CheckExist("Assets/Modules")) fs::create_directory("Assets/Modules");
		for (auto& p : fs::directory_iterator("Assets/Modules"))
			m_ModuleManager->LoadModule(p.path().string());
	}

	void Application::OnRun()
	{
		SCARLET_PROFILE_FUNCTION();

		Timestep timestep = 0.0f;
		std::chrono::time_point<std::chrono::system_clock> StartTime, EndTime;
		while (m_Running)
		{
			StartTime = std::chrono::system_clock::now();
			{
				// Todo: Change to unique system to identify if module has been dropped.
				if (m_Running)
				{
					if (!FileUtils::CheckExist("Assets/Modules")) fs::create_directory("Assets/Modules");
					for (auto& p : fs::directory_iterator("Assets/Modules"))
						m_ModuleManager->LoadModule(p.path().string());
				}
			}
			{
				AppUpdateEvent appEvent(timestep);
				m_EventCallback(appEvent);
			}
			EndTime = std::chrono::system_clock::now();
			timestep = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - StartTime).count();
		}
	}

	void Application::OnStop()
	{
		SCARLET_PROFILE_FUNCTION();

		m_Running = false;
	}

	void Application::OnEvent(Event& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		m_ModuleManager->OnEvent(_Event);

		if (!_Event.Handled) return;
	}

}