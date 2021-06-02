#include "LabelUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> LabelUI::s_Callback = CallbackTable::Create();

	void LabelUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<LabelUI> LabelUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<LabelUI>(_Name);
	}

}