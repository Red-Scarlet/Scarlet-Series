#pragma once
#include <ScarletInterface.h>
#include <ImGui/imgui.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImGuiInstance
	{
	public:
		using CallbackFn = Function<void(Event& _Event, ImGuiContext* _Context)>;

	public:
		ImGuiInstance();
		~ImGuiInstance();

		void OnInit(Event& _Event);
		void OnShutdown(Event& _Event);
		void OnBegin(Event& _Event);
		void OnEnd(Event& _Event);

		void PushFirstCallback(const String& _Name, const CallbackFn& _Callback);
		void PushSecondCallback(const String& _Name, const CallbackFn& _Callback);

	private:
		Vector<Tuple<String, CallbackFn>> m_FirstCallbacks;
		Vector<Tuple<String, CallbackFn>> m_SecondCallbacks;
		ImGuiContext* m_Context;

	public:
		static Ref<ImGuiInstance> Create();
	};

}