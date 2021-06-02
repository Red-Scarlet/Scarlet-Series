#include "ImPanelUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImPanelUI::ImPanelUI(const String& _Name)
		: m_Name(_Name)
	{
		std::cout << "Created ImPanelUI" << std::endl;
	}

	ImPanelUI::~ImPanelUI()
	{
	}

	void ImPanelUI::Attach(const Ref<BaseComponentUI>& _ComponentUI)
	{
		m_Components.push_back(_ComponentUI);
	}

	void ImPanelUI::Detach(const Ref<BaseComponentUI>& _ComponentUI)
	{
		std::remove(m_Components.begin(), m_Components.end(), _ComponentUI);
	}

	void ImPanelUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImPanelUI::GetName()
	{
		return m_Name;
	}

	void ImPanelUI::Draw()
	{
		ImGui::Begin(m_Name.c_str());

		for (Ref<BaseComponentUI> ui : m_Components)
			ui->Draw();

		ImGui::End();
	}

}