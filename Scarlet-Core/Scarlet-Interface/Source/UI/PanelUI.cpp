#include "PanelUI.h"

namespace ScarletInterface {

	Ref<CallbackTable> PanelUI::s_Callback = CallbackTable::Create();

	void PanelUI::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		if (!s_Callback) return;
		s_Callback->Push(_Wrapper);
	}

	Ref<PanelUI> PanelUI::Create(const String& _Name)
	{
		if (!s_Callback || s_Callback->Empty()) 
			return nullptr;
		return s_Callback->Make<PanelUI>(_Name);
	}

} 