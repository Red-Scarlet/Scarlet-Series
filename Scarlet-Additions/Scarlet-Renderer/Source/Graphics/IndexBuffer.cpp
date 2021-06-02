#include "IndexBuffer.h"

namespace Renderer {

	Ref<CallbackTable> IndexBuffer::s_Callback = CallbackTable::Create();

	void IndexBuffer::PushWrapper(const CallbackWrapper& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32& _Size)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<IndexBuffer>(_Size);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32* _Indices, const uint32& _Count)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Make<IndexBuffer>(_Indices, _Count);
	}

}