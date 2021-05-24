#include "IndexBuffer.h"

namespace Renderer {

	Ref<CallbackTable<IndexBuffer>> IndexBuffer::s_Callback = CallbackTable<IndexBuffer>::Create();

	void IndexBuffer::PushWrapper(const CallbackWrapper<IndexBuffer>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32& _Size)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32* _Indices, const uint32& _Count)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Indices, _Count);
	}

}