// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceGLFWImGui.h"

#include <Events/InterfaceEvent.h>
#include "Components/GLFWImGuiComponent.h"

#include <ScarletWindow.h>
#include <ScarletImGui.h>
#include <ImGuiImpl/imgui_impl_glfw.h>

namespace ScarletGLFWImGui {

	void InterfaceGLFWImGui::OnGlobal(Event& _Event)
	{
		_Event.Push(new InterfaceRequirementEvent(this))->Set({
			"Scarlet-ImGui",
			"Scarlet-Window",
			"Scarlet-GLFW"
		});
		if (_Event.Proceed(_Event) == false) return;

		if (!m_Initialized)
		{
			{
				GLFWwindow* nativeWindow = nullptr;
				uint64 windowID = 0;

				_Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
				_Event.Proceed(_Event);

				if (m_Set.size() == 0) return;
				for (Interface i : m_Set)
				{
					Window::WindowComponent* component = {};
					_Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
					_Event.Proceed(_Event);

					if (component)
					{
						if (component->Instance)
						{
							component->Instance->SetCurrent();
							windowID = i;

							Window::WindowComponent& componentRef = *component;
							nativeWindow = (GLFWwindow*)componentRef.Instance->GetNativeWindow();
						}
						else
						{
							_Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
							_Event.Proceed(_Event);
							return;
						}
					}
				}

				//_Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
				_Event.Push(new SignaturePushEvent(this))->Bind<ScarletImGui::ImGuiComponent>();
				_Event.Proceed(_Event);

				for (Interface i : m_Set)
				{
					ScarletImGui::ImGuiComponent* component = {};
					_Event.Push(new ComponentComputeEvent(i))->Retrieve<ScarletImGui::ImGuiComponent>(&component);
					_Event.Proceed(_Event);

					if (component)
					{
						component->WindowAPI = "Scarlet-GLFW";
						Function<void(Interface _i, GLFWwindow* _Window, Event& _Event, ImGuiContext* _Context)> _OnInit = [](Interface _i, GLFWwindow* _Window, Event& _Event, ImGuiContext* _Context) {
							Window::WindowComponent* component = {};
							_Event.Push(new ComponentComputeEvent(_i))->Retrieve<Window::WindowComponent>(&component);
							_Event.Proceed(_Event);

							if (component)
							{
								if (component->Instance)
								{
									component->Instance->SetCurrent();
								}
							}

							ImGui::SetCurrentContext(_Context);
							ImGui_ImplGlfw_InitForOpenGL(_Window, true);
						};

						Function<void(Event& _Event, ImGuiContext* _Context)> _OnShutdown = [](Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGui_ImplGlfw_Shutdown();
						};

						Function<void(Event& _Event, ImGuiContext* _Context)> _OnBegin = [](Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGui_ImplGlfw_NewFrame();
						};

						Function<void(Interface _i, Event& _Event, ImGuiContext* _Context)> _OnEnd = [](Interface _i, Event& _Event, ImGuiContext* _Context) {
							ImGui::SetCurrentContext(_Context);
							ImGuiIO& io = ImGui::GetIO();
							if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
							{
								ImGui::UpdatePlatformWindows();
								ImGui::RenderPlatformWindowsDefault();
							
								Window::WindowComponent* component = {};
								_Event.Push(new ComponentComputeEvent(_i))->Retrieve<Window::WindowComponent>(&component);
								_Event.Proceed(_Event);

								if (component)
								{
									if (component->Instance)
									{
										component->Instance->SetCurrent();
									}
								}

							}
						};

						component->Instance->PushFirstCallback("OnInit", std::bind(_OnInit, windowID, nativeWindow, std::placeholders::_1, std::placeholders::_2));
						component->Instance->PushSecondCallback("OnShutdown", std::bind(_OnShutdown, std::placeholders::_1, std::placeholders::_2));
						component->Instance->PushSecondCallback("OnBegin", std::bind(_OnBegin, std::placeholders::_1, std::placeholders::_2));
						component->Instance->PushSecondCallback("OnEnd", std::bind(_OnEnd, windowID, std::placeholders::_1, std::placeholders::_2));
					}
				}

				_Event.Push(new SignaturePopEvent(this))->Bind<ScarletImGui::ImGuiComponent>();
				_Event.Push(new SignaturePushEvent(this))->Bind<GLFWImGuiComponent>();
				_Event.Push(new ComponentPushEvent(this))->Bind<GLFWImGuiComponent>({});
				_Event.Proceed(_Event);
			}

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceGLFWImGui::OnEditorEvent));
		if (!_Event.Handled) return;
	}

	bool InterfaceGLFWImGui::OnEditorEvent(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}