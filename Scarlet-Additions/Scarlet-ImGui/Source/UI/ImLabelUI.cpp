#include "ImLabelUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImLabelUI::ImLabelUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImLabelUI::~ImLabelUI()
	{
	}

	void ImLabelUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImLabelUI::GetName()
	{
		return m_Name;
	}

	void ImLabelUI::Draw()
	{
		ImGui::Text(m_Name.c_str());
	}

}