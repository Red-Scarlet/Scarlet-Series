#include "RenderCommand.h"

namespace Renderer {

	Ref<CallbackTable> RenderCommand::s_Callback = CallbackTable::Create();

	void RenderCommand::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<RenderCommand> RenderCommand::Create(const String& _Name)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<RenderCommand>(_Name);
	}

}