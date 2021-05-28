#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API ScrollablePanelUI : public BaseUI
	{
	public:
		virtual ~ScrollablePanelUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<ScrollablePanelUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<ScrollablePanelUI>& _Wrapper);
		static Ref<ScrollablePanelUI> Create();
	};

}