#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API TextboxUI : public BaseUI
	{
	public:
		virtual ~TextboxUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<TextboxUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<TextboxUI>& _Wrapper);
		static Ref<TextboxUI> Create();
	};

}