#pragma once

#include <ScarletInterface.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImScrollablePanelUI : public ScrollablePanelUI
	{
	public:
		ImScrollablePanelUI(const String& _Name);
		~ImScrollablePanelUI();

		virtual void Attach(const Ref<BaseComponentUI>& _ComponentUI) override;
		virtual void Detach(const Ref<BaseComponentUI>& _ComponentUI) override;

		virtual void SetName(const String& _Name) override;
		virtual const String& GetName() override;

		virtual void Draw() override;

	private:
		String m_Name;
		Vector<Ref<BaseComponentUI>> m_Components;

	};

}