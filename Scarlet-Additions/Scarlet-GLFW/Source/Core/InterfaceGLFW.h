#pragma once
#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>
#include <ScarletWindow.h>

namespace GLFW {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API InterfaceGLFW : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;

	private:
		void OnLocal(Event& _Event);
		bool OnAppUpdate(AppUpdateEvent& _Event);
		bool OnWindowClose(Window::WindowCloseEvent& _Event);

	private:
		bool m_Running = false, m_Initialized = false;
	};

}

INTERFACE_ENTRYPOINT(GLFW::InterfaceGLFW);