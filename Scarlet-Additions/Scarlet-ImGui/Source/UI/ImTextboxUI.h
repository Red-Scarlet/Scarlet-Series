#pragma once

#include <ScarletInterface.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImTextboxUI : public TextboxUI
	{
	public:
		ImTextboxUI(const String& _Name);
		~ImTextboxUI();

		virtual void SetName(const String& _Name) override;
		virtual const String& GetName() override;

		virtual void Draw() override;

	private:
		String m_Name;
	
	};

}