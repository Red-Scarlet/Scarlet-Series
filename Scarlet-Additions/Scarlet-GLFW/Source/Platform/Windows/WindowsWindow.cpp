// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// WindowsWindow.cpp 02/04/2021 - Functional-Derived Class.
#include "WindowsWindow.h"
#include "Events/WindowEvent.h"

#include <GLFW/glfw3.h>

//#pragma comment(lib, "glfw3.lib")

namespace GLFW {

	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error, const char* description)
	{
		//SCARLET_INTERFACE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		//SCARLET_INTERFACE_INFO("{0}, Creating Window: ({1} x {2})", props.Title, props.Width, props.Height);
		//
		if (true)
		{
			int32 success = glfwInit();
			//SCARLET_INTERFACE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		
		// CHECK FOR API
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		
		m_MainWindow = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(m_MainWindow, &m_Data);

		//GLFWimage images[1];
		//images[0].pixels = stbi_load("Assets/Textures/Concealing.png", &images[0].width, &images[0].height, 0, 4);
		//glfwSetWindowIcon(m_MainWindow, 1, images);
		//stbi_image_free(images[0].pixels);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_MainWindow, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
		
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		
		glfwSetWindowCloseCallback(m_MainWindow, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
		
			data.EventCallback(event);
		});
		
		//glfwSetKeyCallback(m_MainWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		//{
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//	switch (action)
		//	{
		//	case GLFW_PRESS:
		//	{
		//		KeyPressedEvent event(key, 0);
		//		data.EventCallback(event);
		//		break;
		//	}
		//	case GLFW_RELEASE:
		//	{
		//		KeyReleasedEvent event(key);
		//		data.EventCallback(event);
		//		break;
		//	}
		//	case GLFW_REPEAT:
		//	{
		//		KeyPressedEvent event(key, 1);
		//		data.EventCallback(event);
		//		break;
		//	}
		//	}	
		//});
		//
		//glfwSetCharCallback(m_MainWindow, [](GLFWwindow* window, unsigned int keycode)
		//{
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//	KeyTypedEvent event(keycode);
		//	data.EventCallback(event);
		//});
		//
		//glfwSetMouseButtonCallback(m_MainWindow, [](GLFWwindow* window, int button, int action, int mods)
		//{
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//	
		//	switch (action)
		//	{
		//	case GLFW_PRESS:
		//	{
		//		MouseButtonPressedEvent event(button);
		//		data.EventCallback(event);
		//		break;
		//	}
		//	case GLFW_RELEASE:
		//	{
		//		MouseButtonReleasedEvent event(button);
		//		data.EventCallback(event);
		//		break;
		//	}
		//	}
		//});
		//
		//glfwSetScrollCallback(m_MainWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		//{
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//	MouseScrolledEvent event((float)xOffset, (float)yOffset);
		//	data.EventCallback(event);
		//});
		//
		//glfwSetCursorPosCallback(m_MainWindow, [](GLFWwindow* window, double xPos, double yPos)
		//{
		//	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		//
		//	MouseMovedEvent event((float)xPos, (float)yPos);
		//	data.EventCallback(event);
		//});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_MainWindow);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::SetTitle(const String& _Title)
	{
		m_Data.Title = _Title;
		glfwSetWindowTitle(m_MainWindow, m_Data.Title.c_str());
	}

}