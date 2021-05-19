#include "VertexBuffer.h"

namespace Renderer {
	
	//Ref<CallbackTable<VertexBuffer>> VertexBufferCallback = nullptr;

	Ref<VertexBuffer> VertexBuffer::Create(const uint32& _Size)
	{
		if (VertexBufferCallback->Empty()) return nullptr;
		return VertexBufferCallback->Create(_Size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* _Vertices, const uint32& _Size)
	{
		if (VertexBufferCallback->Empty()) return nullptr;
		return VertexBufferCallback->Create(_Vertices, _Size);
	}

}