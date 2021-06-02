#include "ImImageUI.h"

namespace ScarletImGui {

	ImImageUI::ImImageUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImImageUI::~ImImageUI()
	{
	}

	void ImImageUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImImageUI::GetName()
	{
		return m_Name;
	}

	void ScarletImGui::ImImageUI::Draw()
	{
	}


}
