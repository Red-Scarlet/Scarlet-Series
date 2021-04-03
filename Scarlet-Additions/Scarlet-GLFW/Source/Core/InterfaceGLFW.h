// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// InterfaceGLFW.h 02/04/2021 - Interface Class.
#pragma once

#include <ScarletInterface.h>
#include "Events/WindowEvent.h"

namespace GLFW {

	using namespace ScarletInterface;

	class InterfaceGLFW : public InterfaceModule
	{
	public:
		virtual void OnCreate(InterfaceObject& _Interface) override;
		virtual void OnDestroy(InterfaceObject& _Interface) override;
		virtual void OnUpdate(InterfaceObject& _Interface) override;
		virtual void OnEvent(Event& _Event) override;

	private:
		bool OnWindowClose(WindowCloseEvent& _Event);
		bool OnWindowResize(WindowResizeEvent& _Event);

	private:
		bool m_Minimized = false;
		bool m_Running = true;
	};

}