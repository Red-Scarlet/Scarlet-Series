#pragma once

#include <ScarletInterface.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& _VertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& _IndexBuffer) = 0;

		virtual Ref<VertexBuffer> GetVertexBuffer(const uint32& _Index = 0) = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() = 0;

	private:
		static Ref<CallbackTable> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper& _Wrapper);
		static Ref<VertexArray> Create(const String& _Name);
	};

}