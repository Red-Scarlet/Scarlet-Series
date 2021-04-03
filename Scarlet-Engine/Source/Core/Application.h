#pragma once

#include "Core/Common.h"

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
		Application(const String& _ApplicationTitle = "ScarletApplication");
		virtual ~Application() = default;

		void Run();
		void Stop();

		template<typename T>
		void PushModule()
		{
			m_InterfaceController.PushModule<T>();
		}
		template<typename T>
		void PopModule()
		{
			m_InterfaceController.PopModule<T>();
		}
		template<typename T>
		bool HasModule()
		{
			return m_InterfaceController.HasModule<T>();
		}

	private:
		InterfaceController m_InterfaceController;
		String m_Title;
		float32 m_LastFrameTime;
		bool m_Running;

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