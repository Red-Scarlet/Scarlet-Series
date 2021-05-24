#include "VertexBuffer.h"

namespace Renderer {
	
	Ref<CallbackTable<VertexBuffer>> VertexBuffer::s_Callback = CallbackTable<VertexBuffer>::Create();

	void VertexBuffer::PushWrapper(const CallbackWrapper<VertexBuffer>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<VertexBuffer> VertexBuffer::Create(const uint32& _Size)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* _Vertices, const uint32& _Size)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Vertices, _Size);
	}

}