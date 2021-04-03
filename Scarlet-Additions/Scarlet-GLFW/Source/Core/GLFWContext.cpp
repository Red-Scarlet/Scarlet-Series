// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// GLFWContext.cpp 03/04/2021 - Functional Class.
#include "GLFWContext.h"
#include <GLFW/glfw3.h>

namespace GLFW {

	GLFWContext::GLFWContext(GLFWwindow* _WindowHandle)
		: m_WindowHandle(_WindowHandle)
	{
		SCARLET_INTERFACE_ASSERT(_WindowHandle, "GLFWWindow is Nullptr!");
		SCARLET_INTERFACE_INFO("GLFW Thread: {0}", std::this_thread::get_id());

		SetCurrentContext();
	}

	GLFWContext::~GLFWContext()
	{
		glfwTerminate();
	}

	void GLFWContext::SetCurrentContext()
	{
		glfwMakeContextCurrent(m_WindowHandle);
	}

	void GLFWContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void GLFWContext::SwapInterval()
	{
		glfwSwapInterval(0);
	}

	void* GLFWContext::GetProcAddress()
	{
		return (GLFWglproc)glfwGetProcAddress;
	}

}