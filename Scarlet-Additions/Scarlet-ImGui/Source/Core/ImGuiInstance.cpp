#include "ImGuiInstance.h"
#include <ImGui/imgui.h>
#include <ScarletWindow.h>
#include <Events/InterfaceEvent.h>

namespace ScarletImGui {

	ImGuiInstance::ImGuiInstance()
	{
	}

	ImGuiInstance::~ImGuiInstance()
	{
	}

	void ImGuiInstance::OnInit(Event& _Event, const Interface& _Interface)
	{
		IMGUI_CHECKVERSION();
		m_Context = ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		for (auto pair : m_FirstCallbacks)
			if (std::get<String>(pair) == "OnInit")
				std::get<CallbackFn>(pair)(_Event, m_Context);

		for (auto pair : m_SecondCallbacks)
			if (std::get<String>(pair) == "OnInit")
				std::get<CallbackFn>(pair)(_Event, m_Context);
	}

	void ImGuiInstance::OnShutdown(Event& _Event, const Interface& _Interface)
	{
		for (auto pair : m_FirstCallbacks)
			if (std::get<String>(pair) == "OnShutdown")
				std::get<CallbackFn>(pair)(_Event, m_Context);

		for (auto pair : m_SecondCallbacks)
			if (std::get<String>(pair) == "OnShutdown")
				std::get<CallbackFn>(pair)(_Event, m_Context);

		ImGui::DestroyContext();
	}

	void ImGuiInstance::OnBegin(Event& _Event, const Interface& _Interface)
	{
		for (auto pair : m_FirstCallbacks)
			if (std::get<String>(pair) == "OnBegin")
				std::get<CallbackFn>(pair)(_Event, m_Context);

		for (auto pair : m_SecondCallbacks)
			if (std::get<String>(pair) == "OnBegin")
				std::get<CallbackFn>(pair)(_Event, m_Context);
		{
			ImGui::SetCurrentContext(m_Context);
			ImGui::NewFrame();
		}
	}

	void ImGuiInstance::OnEnd(Event& _Event, const Interface& _Interface)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float32)1600, (float32)900);
		ImGui::Render();

		for (auto pair : m_FirstCallbacks)
			if (std::get<String>(pair) == "OnEnd")
				std::get<CallbackFn>(pair)(_Event, m_Context);

		for (auto pair : m_SecondCallbacks)
			if (std::get<String>(pair) == "OnEnd")
				std::get<CallbackFn>(pair)(_Event, m_Context);
	}

	void ImGuiInstance::PushFirstCallback(const String& _Name, const CallbackFn& _Callback)
	{
		m_FirstCallbacks.push_back({ _Name, _Callback });
	}

	void ImGuiInstance::PushSecondCallback(const String& _Name, const CallbackFn& _Callback)
	{
		m_SecondCallbacks.push_back({ _Name, std::move(_Callback) });
	}

	Ref<ImGuiInstance> ImGuiInstance::Create()
	{
		return CreateRef<ImGuiInstance>();
	}

}