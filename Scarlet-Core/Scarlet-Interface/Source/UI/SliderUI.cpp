#include "SliderUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<SliderUI>> SliderUI::s_Callback = CallbackTable<SliderUI>::Create();

	void SliderUI::PushWrapper(const CallbackWrapper<SliderUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<SliderUI> SliderUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}