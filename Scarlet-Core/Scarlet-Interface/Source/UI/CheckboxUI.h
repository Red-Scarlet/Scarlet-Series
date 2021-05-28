#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API CheckboxUI : public BaseUI
	{
	public:
		virtual ~CheckboxUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<CheckboxUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<CheckboxUI>& _Wrapper);
		static Ref<CheckboxUI> Create();
	};

}