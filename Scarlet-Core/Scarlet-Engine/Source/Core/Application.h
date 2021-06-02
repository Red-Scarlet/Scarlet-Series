#pragma once

#include "Core/Common.h"
#include "Interface/ModuleManager.h"
#include <ScarletInterface.h>

#ifdef SCARLET_DIST
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
#else
int main(int argc, char** argv);
#endif

namespace Scarlet {

	using namespace ScarletInterface;

	class Application
	{
	public:
		using EventCallbackFn = Function<void(Event&)>;

	public:
		Application(const String& _ApplicationTitle = "ScarletApplication");
		virtual ~Application() = default;

		void OnRun();
		void OnStop();
		void OnEvent(Event& _Event);

	private:
		EventCallbackFn m_EventCallback = {};
		Ref<ModuleManager> m_ModuleManager = {};

		String m_Title = {};
		uint32 m_NumThreads = {};
		float32 m_LastFrameTime = {};
		bool m_Running = {};

	private:
		static Application* s_Instance;

		#ifdef SCARLET_DIST
		friend int CALLBACK ::WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
		#else
		friend int ::main(int argc, char** argv);
		#endif

	public:
		static Application& Get() { return *s_Instance; }
	};

}

// To be defined in CLIENT
Scarlet::Application* CreateApplication();