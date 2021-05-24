#include "RenderCommand.h"

namespace Renderer {

	Ref<CallbackTable<RenderCommand>> RenderCommand::s_Callback = CallbackTable<RenderCommand>::Create();

	void RenderCommand::PushWrapper(const CallbackWrapper<RenderCommand>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<RenderCommand> RenderCommand::Create(const String& _Name)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Name);
	}

}