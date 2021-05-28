#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API ButtonUI : public BaseUI
	{
	public:
		virtual ~ButtonUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<ButtonUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<ButtonUI>& _Wrapper);
		static Ref<ButtonUI> Create();
	};

}