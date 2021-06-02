#include "VertexBuffer.h"

namespace Renderer {
	
	Ref<CallbackTable> VertexBuffer::s_Callback = CallbackTable::Create();

	void VertexBuffer::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<VertexBuffer> VertexBuffer::Create(const uint32& _Size)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<VertexBuffer>(_Size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* _Vertices, const uint32& _Size)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<VertexBuffer>(_Vertices, _Size);
	}

}