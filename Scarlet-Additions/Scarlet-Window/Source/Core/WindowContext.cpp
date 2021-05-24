#include "WindowContext.h"

namespace Window {

	Ref<CallbackTable<WindowContext>> WindowContext::s_Callback = CallbackTable<WindowContext>::Create();

	void WindowContext::PushWrapper(const CallbackWrapper<WindowContext>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<WindowContext> WindowContext::Create(const WindowProps& _Props)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Props);
	}

}