// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// WindowsWindow.h 02/04/2021 - Functional-Derived Class.
#pragma once

#include "Core/Window.h"
#include <ScarletInterface.h>
#include <GLFW/glfw3.h>

namespace GLFW {

	using namespace ScarletInterface;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		virtual void SetTitle(const String& _Title) override;
		virtual void SetEventCallback(const EventCallbackFn& _Callback) override { m_Data.EventCallback = _Callback; }

		inline const uint32& GetWidth() const override { return m_Data.Width; }
		inline const uint32& GetHeight() const override { return m_Data.Height; }
		inline virtual void* GetNativeWindow() const { return m_MainWindow; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_MainWindow;
		struct WindowData { String Title; uint32 Width, Height; EventCallbackFn EventCallback; } m_Data;

	};

}