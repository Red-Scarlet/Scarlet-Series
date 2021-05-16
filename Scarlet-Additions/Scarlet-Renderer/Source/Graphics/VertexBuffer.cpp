#include "VertexBuffer.h"

#include "Components/AllocateComponent.h"
#include "Core/ResourceQueue.h"

#include "BufferLayout.h"

namespace Renderer {

	VertexBuffer::VertexBuffer(const uint32& _Size)
	{
		m_Data = nullptr;
		m_Size = _Size;

		AllocateComponent Allocate = { ResourceType::VertexBuffer };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	VertexBuffer::VertexBuffer(float32* _Data, const uint32& _Size)
	{
		m_Data = malloc(_Size);
		memmove(m_Data, _Data, _Size);
		m_Size = _Size;

		AllocateComponent Allocate = { ResourceType::VertexBuffer };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::SetData(const void* _Data, const uint32& _Size)
	{
	}

	void VertexBuffer::SetLayout(const BufferLayout& _Layout)
	{
		m_Table.Call("SetLayout", _Layout);
	}

	void VertexBuffer::Bind()
	{
		m_Table.Call("Bind");
	}

	void VertexBuffer::Unbind()
	{
		m_Table.Call("Unbind");
	}

}