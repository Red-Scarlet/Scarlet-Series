#include "ImSliderUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImSliderUI::ImSliderUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImSliderUI::~ImSliderUI()
	{
	}

	void ImSliderUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImSliderUI::GetName()
	{
		return m_Name;
	}

	void ImSliderUI::Draw()
	{
		float32* fl = new float32(3.4f);
		ImGui::SliderFloat(m_Name.c_str(), fl, 0.0, 1.0);
	}

}