// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// GLFWComponent.h 02/04/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include <ScarletWindow.h>

namespace GLFW {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API GLFWComponent
	{
	public:
		Ref<Window::WindowContext> Instance;

		GLFWComponent() = default;
		GLFWComponent(const GLFWComponent&) = default;
		GLFWComponent(const Window::WindowProps& _Props)
		{ 
			Instance = Window::WindowContext::Create(_Props);
		}
	};

}