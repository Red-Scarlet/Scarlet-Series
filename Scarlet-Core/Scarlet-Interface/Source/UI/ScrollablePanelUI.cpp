#include "ScrollablePanelUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> ScrollablePanelUI::s_Callback = CallbackTable::Create();

	void ScrollablePanelUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<ScrollablePanelUI> ScrollablePanelUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty())
			return nullptr;
		return s_Callback->Make<ScrollablePanelUI>(_Name);
	}

}