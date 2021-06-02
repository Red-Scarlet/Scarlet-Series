#include "ImScrollablePanelUI.h"

#include <ImGui/imgui.h>

namespace ScarletImGui {

	ImScrollablePanelUI::ImScrollablePanelUI(const String& _Name)
		: m_Name(_Name)
	{
	}

	ImScrollablePanelUI::~ImScrollablePanelUI()
	{
	}

	void ImScrollablePanelUI::Attach(const Ref<BaseComponentUI>& _ComponentUI)
	{
		m_Components.push_back(_ComponentUI);
	}

	void ImScrollablePanelUI::Detach(const Ref<BaseComponentUI>& _ComponentUI)
	{
		std::remove(m_Components.begin(), m_Components.end(), _ComponentUI);
	}

	void ImScrollablePanelUI::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	const String& ImScrollablePanelUI::GetName()
	{
		return m_Name;
	}

	void ImScrollablePanelUI::Draw()
	{
		ImGui::Begin(m_Name.c_str());

		for (Ref<BaseComponentUI> ui : m_Components)
			ui->Draw();

		ImGui::End();
	}

}