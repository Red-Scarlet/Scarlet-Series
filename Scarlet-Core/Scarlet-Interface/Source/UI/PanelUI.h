#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API PanelUI : public BaseUI
	{
	public:
		virtual ~PanelUI () = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<PanelUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<PanelUI>& _Wrapper);
		static Ref<PanelUI> Create();
	};

}