#include "ImTextboxUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImTextboxUI::ImTextboxUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImTextboxUI::~ImTextboxUI()
	{
	}

	void ImTextboxUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImTextboxUI::GetName()
	{
		return m_Name;
	}

	void ImTextboxUI::Draw()
	{
		//ImGui::InputText()
	}
}