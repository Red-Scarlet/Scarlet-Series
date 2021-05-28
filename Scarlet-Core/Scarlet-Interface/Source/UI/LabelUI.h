#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API LabelUI : public BaseUI
	{
	public:
		virtual ~LabelUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<LabelUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<LabelUI>& _Wrapper);
		static Ref<LabelUI> Create();
	};

}