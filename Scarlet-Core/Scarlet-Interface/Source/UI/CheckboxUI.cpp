#include "CheckboxUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> CheckboxUI::s_Callback = CallbackTable::Create();

	void CheckboxUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<CheckboxUI> CheckboxUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<CheckboxUI>(_Name);
	}

}