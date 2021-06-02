#include "WindowContext.h"

namespace Window {

	Ref<CallbackTable> WindowContext::s_Callback = CallbackTable::Create();

	void WindowContext::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<WindowContext> WindowContext::Create(const WindowProps& _Props)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<WindowContext>(_Props);
	}

}