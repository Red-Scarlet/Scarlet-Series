#pragma once

#include <ScarletInterface.h>

namespace ScarletImGui {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ImImageUI : public ImageUI
	{
	public:
		ImImageUI(const String& _Name);
		~ImImageUI();

		virtual void SetName(const String& _Name) override;
		virtual const String& GetName() override;

		virtual void Draw() override;

	private:
		String m_Name;
	};

}