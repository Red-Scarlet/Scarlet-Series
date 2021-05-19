#include "IndexBuffer.h"

namespace Renderer {

	//Ref<CallbackTable<IndexBuffer>> IndexBufferCallback = nullptr;

	Ref<IndexBuffer> IndexBuffer::Create(const uint32& _Size)
	{
		if (IndexBufferCallback->Empty()) return nullptr;
		return IndexBufferCallback->Create(_Size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32* _Indices, const uint32& _Count)
	{
		if (IndexBufferCallback->Empty()) return nullptr;
		return IndexBufferCallback->Create(_Indices, _Count);
	}

}