// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// WindowsWindow.cpp 02/04/2021 - Functional-Derived Class.
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>

namespace GLFW {

	WindowsWindow::WindowsWindow(const Window::WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		int32 success = glfwInit();
		if (success == -1)
		{
			std::cout << "GLFW ERROR!" << std::endl;
			__debugbreak();
		}

		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		m_MainWindow = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_MainWindow);
		glfwSetWindowUserPointer(m_MainWindow, &m_Data);

		glfwSetWindowSizeCallback(m_MainWindow, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			Window::WindowResizeEvent resizeEvent(width, height);
			data.EventCallback(resizeEvent);
		});

		glfwSetWindowCloseCallback(m_MainWindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			Window::WindowCloseEvent closeEvent;

			data.EventCallback(closeEvent);
		});

		glfwSwapInterval(0);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_MainWindow);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_MainWindow);
		glfwPollEvents();
	}

	void WindowsWindow::SetCurrent()
	{
		glfwMakeContextCurrent(m_MainWindow);
	}

	void WindowsWindow::SetTitle(const String& _Title)
	{
		m_Data.Title = _Title;
		glfwSetWindowTitle(m_MainWindow, m_Data.Title.c_str());
	}

	void* WindowsWindow::GetProcAddress() const
	{
		return glfwGetProcAddress;
	}

}