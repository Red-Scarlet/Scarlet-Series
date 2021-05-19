#include "RenderCommand.h"

namespace Renderer {

	//Ref<CallbackTable<RenderCommand>> RenderCommandCallback = nullptr;

	Ref<RenderCommand> RenderCommand::Create(const String& _Name)
	{
		if (RenderCommandCallback->Empty()) return nullptr;
		return RenderCommandCallback->Create(_Name);
	}

}