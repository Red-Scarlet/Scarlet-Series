#include "CheckboxUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<CheckboxUI>> CheckboxUI::s_Callback = CallbackTable<CheckboxUI>::Create();

	void CheckboxUI::PushWrapper(const CallbackWrapper<CheckboxUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<CheckboxUI> CheckboxUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}