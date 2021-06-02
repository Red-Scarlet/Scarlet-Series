#include "TextboxUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> TextboxUI::s_Callback = CallbackTable::Create();

	void TextboxUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<TextboxUI> TextboxUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<TextboxUI>(_Name);
	}

}