#include "TextboxUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<TextboxUI>> TextboxUI::s_Callback = CallbackTable<TextboxUI>::Create();

	void TextboxUI::PushWrapper(const CallbackWrapper<TextboxUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<TextboxUI> TextboxUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}