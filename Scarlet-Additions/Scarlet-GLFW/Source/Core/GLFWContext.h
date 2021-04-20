// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// GLFWContext.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>

struct SCARLET_INTERFACE_API GLFWwindow;

namespace GLFW {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API GLFWContext
	{
	public:
		GLFWContext(GLFWwindow* _WindowHandle);
		virtual ~GLFWContext();

		void SetCurrentContext();
		void SwapBuffers();
		void SwapInterval();

		void* GetProcAddress();

	private:
		GLFWwindow* m_WindowHandle;

	public:
		static Ref<GLFWContext> Create(GLFWwindow* _WindowHandle)
		{ return CreateRef<GLFWContext>(_WindowHandle); }
	};

}