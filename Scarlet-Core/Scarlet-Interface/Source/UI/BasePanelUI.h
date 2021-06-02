#pragma once

#include "Core/Common.h"
#include "UI/BaseComponentUI.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API BasePanelUI
	{
	public:
		virtual ~BasePanelUI() = default;

		virtual void Attach(const Ref<BaseComponentUI>& _ComponentUI) = 0;
		virtual void Detach(const Ref<BaseComponentUI>& _ComponentUI) = 0;

		virtual void SetName(const String& _Name) = 0;
		virtual const String& GetName() = 0;

		virtual void Draw() = 0;
	};

}