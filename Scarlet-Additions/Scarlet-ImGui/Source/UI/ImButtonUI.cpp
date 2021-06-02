#include "ImButtonUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImButtonUI::ImButtonUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImButtonUI::~ImButtonUI()
	{
	}

	void ImButtonUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImButtonUI::GetName()
	{
		return m_Name;
	}

	void ImButtonUI::Draw()
	{
		ImGui::Button(m_Name.c_str(), ImVec2({ 96, 32 }));
	}
}