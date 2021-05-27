// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// WindowsWindow.h 02/04/2021 - Functional-Derived Class.
#pragma once

#include <ScarletInterface.h>
#include <ScarletWindow.h>

struct SCARLET_INTERFACE_API GLFWwindow;

namespace GLFW {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API WindowsWindow : public Window::WindowContext
	{
	public:
		WindowsWindow(const Window::WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;
		virtual void SetCurrent() override;
		virtual void SetTitle(const String& _Title) override;
		virtual void SetEventCallback(const EventCallbackFn& _Callback) override { m_Data.EventCallback = _Callback; }

		const uint32& GetWidth() const override { return m_Data.Width; }
		const uint32& GetHeight() const override { return m_Data.Height; }

		virtual void* GetNativeWindow() const { return m_MainWindow; }
		virtual void* GetProcAddress() const;

	private:
		GLFWwindow* m_MainWindow;
		struct WindowData { String Title; uint32 Width, Height; EventCallbackFn EventCallback; } m_Data;
	};

}