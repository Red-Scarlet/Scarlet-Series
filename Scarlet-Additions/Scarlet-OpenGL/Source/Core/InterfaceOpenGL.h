// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// InterfaceGL.h 02/04/2021 - Interface Class.
#pragma once
#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>
#include "Core/OpenGLContext.h"

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API InterfaceOpenGL : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;
		virtual void OnLocal(Event& _Event) override;

	private:
		bool OnAppUpdate(AppUpdateEvent& _Event);

	private:
		Ref<OpenGLContext> m_Context;
		bool m_Running = false, m_Initialized = false;
	};

}

INTERFACE_ENTRYPOINT(OpenGL::InterfaceOpenGL);