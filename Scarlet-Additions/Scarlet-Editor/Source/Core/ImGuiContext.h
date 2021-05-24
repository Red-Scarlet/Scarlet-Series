#pragma once

#include <ScarletInterface.h>
#include <unordered_map>

namespace Editor {

	using namespace ScarletInterface;

	class ImGuiContext
	{
	public:
		ImGuiContext();
		virtual ~ImGuiContext();

		void OnBegin();
		void OnEnd();

	private:
		void SetDarkThemeColors();

	private:
		bool m_BlockEvents = true;
		float32 m_Time = 0.0f;

	public:
		static Ref<ImGuiContext> Create()
		{ return CreateRef<ImGuiContext>(); }
	};

}