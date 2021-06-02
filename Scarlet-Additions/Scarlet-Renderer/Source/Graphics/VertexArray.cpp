#include "VertexArray.h"

namespace Renderer {

	Ref<CallbackTable> VertexArray::s_Callback = CallbackTable::Create();

	void VertexArray::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<VertexArray> VertexArray::Create(const String& _Name)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<VertexArray>(_Name);
	}

}