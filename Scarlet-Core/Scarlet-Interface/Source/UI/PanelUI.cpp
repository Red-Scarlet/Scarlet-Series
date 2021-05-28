#include "PanelUI.h"

namespace ScarletInterface {

	Ref<CallbackTable<PanelUI>> PanelUI::s_Callback = CallbackTable<PanelUI>::Create();

	void PanelUI::PushWrapper(const CallbackWrapper<PanelUI>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<PanelUI> PanelUI::Create()
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create("");
	}

}