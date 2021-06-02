#include "SliderUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> SliderUI::s_Callback = CallbackTable::Create();

	void SliderUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<SliderUI> SliderUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<SliderUI>(_Name);
	}

}