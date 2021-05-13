#pragma once
#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>

#include "Core/Window.h"
#include "Core/GLFWContext.h"
#include "Events/WindowEvent.h"

namespace GLFW {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API InterfaceGLFW : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;
		virtual void OnLocal(Event& _Event) override;

	private:
		bool OnAppUpdate(AppUpdateEvent& _Event);
		bool OnWindowClose(WindowCloseEvent& _Event);
		bool OnWindowResize(WindowResizeEvent& _Event);

	private:
		bool m_Running = false, m_Initialized = false, m_Minimized = false;
	};

}

INTERFACE_ENTRYPOINT(GLFW::InterfaceGLFW);