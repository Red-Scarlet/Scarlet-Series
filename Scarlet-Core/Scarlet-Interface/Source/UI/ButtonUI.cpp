#include "ButtonUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<ButtonUI>> ButtonUI::s_Callback = CallbackTable<ButtonUI>::Create();

	void ButtonUI::PushWrapper(const CallbackWrapper<ButtonUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<ButtonUI> ButtonUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}