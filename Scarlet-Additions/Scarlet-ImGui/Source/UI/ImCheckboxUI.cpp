#include "ImCheckboxUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImCheckboxUI::ImCheckboxUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImCheckboxUI::~ImCheckboxUI()
	{
	}

	void ImCheckboxUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImCheckboxUI::GetName()
	{
		return m_Name;
	}

	void ImCheckboxUI::Draw()
	{
		bool* value = new bool(false);
		ImGui::Checkbox(m_Name.c_str(), value);
	}


}
