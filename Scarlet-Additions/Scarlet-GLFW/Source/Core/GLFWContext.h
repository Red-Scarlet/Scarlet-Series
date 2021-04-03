// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// GLFWContext.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>

struct GLFWwindow;

namespace GLFW {

	using namespace ScarletInterface;

	class GLFWContext
	{
	public:
		GLFWContext(GLFWwindow* _WindowHandle);
		~GLFWContext();

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