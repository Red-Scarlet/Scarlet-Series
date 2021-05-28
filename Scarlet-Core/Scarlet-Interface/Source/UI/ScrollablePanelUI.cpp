#include "ScrollablePanelUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<ScrollablePanelUI>> ScrollablePanelUI::s_Callback = CallbackTable<ScrollablePanelUI>::Create();

	void ScrollablePanelUI::PushWrapper(const CallbackWrapper<ScrollablePanelUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<ScrollablePanelUI> ScrollablePanelUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}