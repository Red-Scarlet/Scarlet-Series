#pragma once

#include "Core/Common.h"
#include "UI/BaseUI.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API ImageUI : public BaseUI
	{
	public:
		virtual ~ImageUI() = default;

	private:
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable<ImageUI>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<ImageUI>& _Wrapper);
		static Ref<ImageUI> Create();
	};

}