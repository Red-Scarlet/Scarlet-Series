#pragma once

#include <ScarletInterface.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImSliderUI : public SliderUI
	{
	public:
		ImSliderUI(const String& _Name);
		~ImSliderUI();

		virtual void SetName(const String& _Name) override;
		virtual const String& GetName() override;

		virtual void Draw() override;

	private:
		String m_Name;

	};

}