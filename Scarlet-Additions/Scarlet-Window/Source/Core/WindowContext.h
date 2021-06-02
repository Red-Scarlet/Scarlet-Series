// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// Window.h 02/04/2021 - Functional-Abstracted Class.
#pragma once

#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>

namespace Window {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API WindowProps
	{
	public:
		String Title;
		uint32 Width, Height;

		WindowProps(const String& _Title = "Scarlet", const uint32& _Width = 1600, const uint32& _Height = 900)
			: Title(_Title), Width(_Width), Height(_Height)
		{
		}
	};

	class SCARLET_INTERFACE_API WindowContext
	{
	public:
		using EventCallbackFn = Function<void(Event&)>;

	public:
		virtual ~WindowContext() = default;

		virtual void OnUpdate() = 0;
		virtual void SetCurrent() = 0;
		virtual void SetTitle(const String& _Title) = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual const uint32& GetWidth() const = 0;
		virtual const uint32& GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual void* GetProcAddress() const = 0;

	private:
		static Ref<CallbackTable> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper& _Wrapper);
		static Ref<WindowContext> Create(const WindowProps& _Props);
	};

}