#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API SliderUI : public BaseUI
	{
	public:
		virtual ~SliderUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<SliderUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<SliderUI>& _Wrapper);
		static Ref<SliderUI> Create();
	};

}