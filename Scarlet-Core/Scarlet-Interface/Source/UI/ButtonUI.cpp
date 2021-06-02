#include "ButtonUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> ButtonUI::s_Callback = CallbackTable::Create();

	void ButtonUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<ButtonUI> ButtonUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<ButtonUI>(_Name);
	}

}