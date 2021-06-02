#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const uint32& GetCount() const = 0;

	private:
		static Ref<CallbackTable> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper& _Wrapper);
		static Ref<IndexBuffer> Create(const uint32& _Size);
		static Ref<IndexBuffer> Create(uint32* _Indices, const uint32& _Count);
	};

}