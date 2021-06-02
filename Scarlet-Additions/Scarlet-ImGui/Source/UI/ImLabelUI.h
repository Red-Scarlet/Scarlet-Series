#pragma once

#include <ScarletInterface.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImLabelUI : public LabelUI
	{
	public:
		ImLabelUI(const String& _Name);
		~ImLabelUI();

		virtual void SetName(const String& _Name) override;
		virtual const String& GetName() override;

		virtual void Draw() override;

	private:
		String m_Name;
	};

}