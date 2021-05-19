#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"
#include "BufferLayout.h"

namespace Renderer {

	using namespace ScarletInterface;
	
	class SCARLET_INTERFACE_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& _Layout) = 0;
		virtual void SetData(const void* _Data, const uint32& _Size) = 0;

	public:
		static Ref<VertexBuffer> Create(const uint32& _Size);
		static Ref<VertexBuffer> Create(float* _Vertices, const uint32& _Size);
	};

	static Ref<CallbackTable<VertexBuffer>> VertexBufferCallback;

}