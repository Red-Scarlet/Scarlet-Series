// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceImGui.h"

#include <Events/InterfaceEvent.h>
#include "Components/ImGuiComponent.h"
#include "ImGuiInstance.h"

#include <ImGui/imgui.h>
#include <ScarletWindow.h>

#include "UI/ImButtonUI.h"
#include "UI/ImCheckboxUI.h"
#include "UI/ImImageUI.h"
#include "UI/ImLabelUI.h"
#include "UI/ImPanelUI.h"
#include "UI/ImScrollablePanelUI.h"
#include "UI/ImSliderUI.h"
#include "UI/ImTextboxUI.h"

namespace ScarletImGui {

	void InterfaceImGui::OnGlobal(Event& _Event)
	{
		this->SetCallbacks(_Event);

		if (!m_Initialized)
		{
			//_Event.Push(new InterfaceSetCallbacks(this));
			_Event.Push(new SignaturePushEvent(this))->Bind<ImGuiComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<ImGuiComponent>(ImGuiInstance::Create());
			_Event.Proceed(_Event);

			{
				Function<Ref<ScarletInterface::ButtonUI>(const String& _Name)> _ButtonUI = [](const String& _Name) { return CreateRef<ImButtonUI>(_Name); };
				auto _ButtonUIBind = std::bind(_ButtonUI, std::placeholders::_1);
				CallbackWrapper _ButtonUIWrapper;
				_ButtonUIWrapper.Bind<ScarletInterface::ButtonUI, decltype(_ButtonUIBind), const String&>(_ButtonUIBind);
				ScarletInterface::ButtonUI::PushWrapper(_ButtonUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::CheckboxUI>(const String& _Name)> _CheckboxUI = [](const String& _Name) { return CreateRef<ImCheckboxUI>(_Name); };
				auto _CheckboxUIBind = std::bind(_CheckboxUI, std::placeholders::_1);
				CallbackWrapper _CheckboxUIWrapper;
				_CheckboxUIWrapper.Bind<ScarletInterface::CheckboxUI, decltype(_CheckboxUIBind), const String&>(_CheckboxUIBind);
				ScarletInterface::CheckboxUI::PushWrapper(_CheckboxUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::ImageUI>(const String& _Name)> _ImageUI = [](const String& _Name) { return CreateRef<ImImageUI>(_Name); };
				auto _ImageUIBind = std::bind(_ImageUI, std::placeholders::_1);
				CallbackWrapper _ImageUIWrapper;
				_ImageUIWrapper.Bind<ScarletInterface::ImageUI, decltype(_ImageUIBind), const String&>(_ImageUIBind);
				ScarletInterface::ImageUI::PushWrapper(_ImageUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::LabelUI>(const String& _Name)> _LabelUI = [](const String& _Name) { return CreateRef<ImLabelUI>(_Name); };
				auto _LabelUIBind = std::bind(_LabelUI, std::placeholders::_1);
				CallbackWrapper _LabelUIWrapper;
				_LabelUIWrapper.Bind<ScarletInterface::LabelUI, decltype(_LabelUIBind), const String&>(_LabelUIBind);
				ScarletInterface::LabelUI::PushWrapper(_LabelUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::PanelUI>(const String& _Name)> _PanelUI = [](const String& _Name) { return CreateRef<ImPanelUI>(_Name); };
				auto _PanelUIBind = std::bind(_PanelUI, std::placeholders::_1);
				CallbackWrapper _PanelUIWrapper;
				_PanelUIWrapper.Bind<ScarletInterface::PanelUI, decltype(_PanelUIBind), const String&>(_PanelUIBind);
				ScarletInterface::PanelUI::PushWrapper(_PanelUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::ScrollablePanelUI>(const String& _Name)> _ScrollablePanelUI = [](const String& _Name) { return CreateRef<ImScrollablePanelUI>(_Name); };
				auto _ScrollablePanelUIBind = std::bind(_ScrollablePanelUI, std::placeholders::_1);
				CallbackWrapper _ScrollablePanelUIWrapper;
				_ScrollablePanelUIWrapper.Bind<ScarletInterface::ScrollablePanelUI, decltype(_ScrollablePanelUIBind), const String&>(_ScrollablePanelUIBind);
				ScarletInterface::ScrollablePanelUI::PushWrapper(_ScrollablePanelUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::SliderUI>(const String& _Name)> _SliderUI = [](const String& _Name) { return CreateRef<ImSliderUI>(_Name); };
				auto _SliderUIBind = std::bind(_SliderUI, std::placeholders::_1);
				CallbackWrapper _SliderUIWrapper;
				_SliderUIWrapper.Bind<ScarletInterface::SliderUI, decltype(_SliderUIBind), const String&>(_SliderUIBind);
				ScarletInterface::SliderUI::PushWrapper(_SliderUIWrapper);
			}

			{
				Function<Ref<ScarletInterface::TextboxUI>(const String& _Name)> _TextboxUI = [](const String& _Name) { return CreateRef<ImTextboxUI>(_Name); };
				auto _TextboxUIBind = std::bind(_TextboxUI, std::placeholders::_1);
				CallbackWrapper _TextboxUIWrapper;
				_TextboxUIWrapper.Bind<ScarletInterface::TextboxUI, decltype(_TextboxUIBind), const String&>(_TextboxUIBind);
				ScarletInterface::TextboxUI::PushWrapper(_TextboxUIWrapper);
			}

			_Event.Push(new EditorHookEvent(this))->Bind(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceImGui::OnEditorPanelDraw));
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceImGui::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfaceImGui::OnEditorPanelDraw(EditorPanelDrawEvent& _Event)
	{
		for (uint32 i = 0; i < _Event.GetSize(); i++)
		{
			Ref<BasePanelUI> panel = _Event.GetUI(i);
			if (std::count(m_UIComponents.begin(), m_UIComponents.end(), panel) == false)
				m_UIComponents.push_back(panel);
		}

		return true;
	}

	bool InterfaceImGui::OnAppUpdate(AppUpdateEvent& _Event)
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
				static bool opt_fullscreen_persistant = true;
				bool opt_fullscreen = opt_fullscreen_persistant;
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

				ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
				if (opt_fullscreen) 
				{
					ImGuiViewport* viewport = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(viewport->Pos);
					ImGui::SetNextWindowSize(viewport->Size);
					ImGui::SetNextWindowViewport(viewport->ID);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
					window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}

				if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
					window_flags |= ImGuiWindowFlags_NoBackground;

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", (bool*)true, window_flags);
				ImGui::PopStyleVar();

				if (opt_fullscreen)
					ImGui::PopStyleVar(2);

				ImGuiIO& io = ImGui::GetIO();
				ImGuiStyle& style = ImGui::GetStyle();
				float32 minWinSize = style.WindowMinSize.x;
				style.WindowMinSize.x = 370.0f;

				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) 
				{
					ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}

				style.WindowMinSize.x = minWinSize;
				for (Ref<BasePanelUI> ui : m_UIComponents)
					ui->Draw();

				ImGui::End();
			}
			component->Instance->OnEnd(_Event, windowInterface);
			m_UIComponents.clear();
		}

		if (!m_Running)
		{
			component->Instance->OnShutdown(_Event, windowInterface);
		}

		return m_Running;
	}

}