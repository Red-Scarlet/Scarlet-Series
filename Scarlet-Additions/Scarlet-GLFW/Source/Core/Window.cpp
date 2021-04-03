// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// Window.cpp 02/04/2021 - Functional-Abstracted Class.
#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace GLFW {

	Ref<Window> Window::Create(const WindowProps& props)
	{
		return CreateRef<WindowsWindow>(props);
	}

}