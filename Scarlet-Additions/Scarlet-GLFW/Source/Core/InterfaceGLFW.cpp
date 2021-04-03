// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// InterfaceGLFW.cpp 02/04/2021 - Interface Class.
#include "InterfaceGLFW.h"
#include "Components/GLFWComponent.h"

namespace GLFW {

	#define BIND_EVENT_FN(x) std::bind(&InterfaceGLFW::x, this, std::placeholders::_1)

	void InterfaceGLFW::OnCreate(InterfaceObject& _Interface)
	{
		this->RegisterComponent<GLFWComponent>();
		this->PushSignature<InterfaceGLFW, GLFWComponent>();

		WindowProps WindowProperties;
		WindowProperties.Title = "ScarletGLFW";
		GLFWComponent& component = _Interface.AddComponent<GLFWComponent>(WindowProperties);
		component.Instance->SetEventCallback(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFW::OnEvent));
		m_Running = true;
	}

	void InterfaceGLFW::OnDestroy(InterfaceObject& _Interface)
	{
	}

	void InterfaceGLFW::OnUpdate(InterfaceObject& _Interface)
	{
		if (m_Running) {
			GLFWComponent& component = _Interface.GetComponent<GLFWComponent>();
			component.Instance->OnUpdate();
			component.MainContext->SwapBuffers();
		}

		if (!m_Running) {
			if (_Interface.HasComponent<GLFWComponent>())
			{
				GLFWComponent& component = _Interface.GetComponent<GLFWComponent>();
				component.Instance.reset();
				component.MainContext.reset();
				_Interface.RemoveComponent<GLFWComponent>();
			}
		}
	}

	void InterfaceGLFW::OnEvent(Event& _Event)
	{
		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		this->PopSignature<InterfaceGLFW, GLFWComponent>();
		for (InterfaceObject& object : this->GetInterfaceObjects()) {
			IdentifierComponent& identifierComponent = object.GetComponent<IdentifierComponent>();
			Ref<InterfaceModule> mod = this->GetModule<InterfaceModule>(identifierComponent.Identifer);
			mod->OnEvent(_Event);
		}
		this->PushSignature<InterfaceGLFW, GLFWComponent>();
	}

	bool InterfaceGLFW::OnWindowClose(WindowCloseEvent& _Event)
	{
		m_Running = false;
		return true;
	}

	bool InterfaceGLFW::OnWindowResize(WindowResizeEvent& _Event)
	{
		if (_Event.GetWidth() == 0 || _Event.GetHeight() == 0) m_Minimized = true;
		else m_Minimized = false;
		return false;
	}

}