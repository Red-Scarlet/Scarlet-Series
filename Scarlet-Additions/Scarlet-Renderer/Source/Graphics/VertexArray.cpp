#include "VertexArray.h"

namespace Renderer {

	Ref<CallbackTable<VertexArray>> VertexArray::s_Callback = CallbackTable<VertexArray>::Create();

	void VertexArray::PushWrapper(const CallbackWrapper<VertexArray>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<VertexArray> VertexArray::Create(const String& _Name)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Name);
	}

}