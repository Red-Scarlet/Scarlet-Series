#pragma once

#include <ScarletInterface.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImButtonUI : public ButtonUI
	{
	public:
		ImButtonUI(const String& _Name);
		~ImButtonUI();

		virtual void SetName(const String& _Name) override;
		virtual const String& GetName() override;

	private:
		virtual void Draw() override;

	private:
		String m_Name;
	};

}