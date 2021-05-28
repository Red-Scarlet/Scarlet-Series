#include "LabelUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<LabelUI>> LabelUI::s_Callback = CallbackTable<LabelUI>::Create();

	void LabelUI::PushWrapper(const CallbackWrapper<LabelUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<LabelUI> LabelUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}