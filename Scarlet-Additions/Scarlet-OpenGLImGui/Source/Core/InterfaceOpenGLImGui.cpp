// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceOpenGLImGui.h"

#include <Events/InterfaceEvent.h>
#include "Components/OpenGLImGuiComponent.h"

#include <ScarletRenderer.h>
#include <ScarletImGui.h>
#include <ImGuiImpl/imgui_impl_opengl3.h>

#include <ScarletWindow.h>

namespace ScarletOpenGLImGui {

	void InterfaceOpenGLImGui::OnGlobal(Event& _Event)
	{
		_Event.Push(new InterfaceRequirementEvent(this))->Set({
			"Scarlet-Window",
			"Scarlet-Renderer",
			"Scarlet-OpenGL",
			"Scarlet-ImGui",
		});
		if (_Event.Proceed(_Event) == false) return;

		if (!m_Initialized)
		{
			{
				_Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
				_Event.Proceed(_Event);
				
				for (Interface i : m_Set)
				{
					Window::WindowComponent* component = {};
					_Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
					_Event.Proceed(_Event);
					if (component)
					{
						if (component->Instance)
							component->Instance->SetCurrent();
						else
						{
							_Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
							_Event.Proceed(_Event);
							return;
						}
					}
				}
				
				_Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
				_Event.Push(new SignaturePushEvent(this))->Bind<ScarletImGui::ImGuiComponent>();
				_Event.Proceed(_Event);

				for (Interface i : m_Set)
				{
					ScarletImGui::ImGuiComponent* component = {};
					_Event.Push(new ComponentComputeEvent(i))->Retrieve<ScarletImGui::ImGuiComponent>(&component);
					_Event.Proceed(_Event);

					if (component)
					{
						component->RendererAPI = "Scarlet-OpenGL";
						Function<void(Event& _Event, ImGuiContext* _Context)> _OnInit = [](Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGui_ImplOpenGL3_Init("#version 410");
						};

						Function<void(Event& _Event, ImGuiContext* _Context)> _OnShutdown = [](Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGui_ImplOpenGL3_Shutdown();
						};

						Function<void(Event& _Event, ImGuiContext* _Context)> _OnBegin = [](Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGui_ImplOpenGL3_NewFrame();
						};

						Function<void(Event& _Event, ImGuiContext* _Context)> _OnEnd = [](Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
						};

						component->Instance->PushSecondCallback("OnInit", std::bind(_OnInit, std::placeholders::_1, std::placeholders::_2));
						component->Instance->PushFirstCallback("OnShutdown", std::bind(_OnShutdown, std::placeholders::_1, std::placeholders::_2));
						component->Instance->PushFirstCallback("OnBegin", std::bind(_OnBegin, std::placeholders::_1, std::placeholders::_2));
						component->Instance->PushFirstCallback("OnEnd", std::bind(_OnEnd, std::placeholders::_1, std::placeholders::_2));
					}
				}

				_Event.Push(new SignaturePopEvent(this))->Bind<ScarletImGui::ImGuiComponent>();
				_Event.Push(new SignaturePushEvent(this))->Bind<OpenGLImGuiComponent>();
				_Event.Push(new ComponentPushEvent(this))->Bind<OpenGLImGuiComponent>({});
				_Event.Proceed(_Event);
			}

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceOpenGLImGui::OnEditorEvent));
		if (!_Event.Handled) return;
	}

	bool InterfaceOpenGLImGui::OnEditorEvent(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}