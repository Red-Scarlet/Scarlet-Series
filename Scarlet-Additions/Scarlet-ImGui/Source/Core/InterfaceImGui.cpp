// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceImGui.h"

#include <Events/InterfaceEvent.h>
#include "Components/ImGuiComponent.h"
#include "ImGuiInstance.h"

#include <ImGui/imgui.h>
#include <ScarletWindow.h>

namespace ScarletImGui {

	void InterfaceImGui::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<ImGuiComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<ImGuiComponent>(ImGuiInstance::Create());
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceImGui::OnEditorEvent));
		if (!_Event.Handled) return;
	}

	void InterfaceImGui::OnEditor(Event& _Event)
	{
		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceImGui::OnEditorEvent));
		if (!_Event.Handled) return;
	}

	bool InterfaceImGui::OnEditorEvent(AppUpdateEvent& _Event)
	{
		Interface windowInterface = uint64_max;
		ImGuiComponent* component = {};
		_Event.Push(new ComponentComputeEvent(this))->Retrieve<ScarletImGui::ImGuiComponent>(&component);
		_Event.Proceed(_Event);

		if (m_Running && component)
		{
			if (component->WindowAPI == "None" || component->RendererAPI == "None") return false;
			if (component->Initialized == false) 
			{
				if (windowInterface == uint64_max)
				{
					_Event.Push(new SignaturePopEvent(this))->Bind<ImGuiComponent>();
					_Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
					_Event.Proceed(_Event);

					for (Interface i : m_Set)
					{
						Window::WindowComponent* component = {};
						_Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
						_Event.Proceed(_Event);

						if (component) { windowInterface = i; break; }
					}

					_Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
					_Event.Push(new SignaturePushEvent(this))->Bind<ImGuiComponent>();
					_Event.Proceed(_Event);
				}

				component->Instance->OnInit(_Event, windowInterface);
				component->Initialized = true; 
			}

			component->Instance->OnBegin(_Event, windowInterface);
			{

				// Invoke a dispatcher 

				ImGui::ShowDemoWindow((bool*)true);
			}
			component->Instance->OnEnd(_Event, windowInterface);
		}

		if (!m_Running)
		{
			component->Instance->OnShutdown(_Event, windowInterface);
		}

		return m_Running;
	}
}