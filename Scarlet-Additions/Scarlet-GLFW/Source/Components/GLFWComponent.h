// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// GLFWComponent.h 02/04/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

#include "Core/Window.h"
#include "Core/GLFWContext.h"

namespace GLFW {

	struct GLFWComponent
	{
	public:
		ScarletInterface::Ref<Window> Instance;
		ScarletInterface::Ref<GLFWContext> Context;

		GLFWComponent() = default;
		GLFWComponent(const GLFWComponent&) = default;
		GLFWComponent(const WindowProps& _Props)
		{ 
			Instance = Window::Create(_Props);
			Context = GLFWContext::Create((GLFWwindow*)Instance->GetNativeWindow());
		}
	};

}