#include "IndexBuffer.h"

#include "Components/AllocateComponent.h"
#include "Core/ResourceQueue.h"

#include "BufferLayout.h"

namespace Renderer {

	IndexBuffer::IndexBuffer(const uint32& _Size, const uint32& _Count)
		: m_Count(_Count)
	{
		m_Data = nullptr;
		m_Size = _Size;

		AllocateComponent Allocate = { ResourceType::IndexBuffer };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	IndexBuffer::IndexBuffer(uint32* _Data, const uint32& _Size, const uint32& _Count)
		: m_Count(_Count)
	{
		m_Data = malloc(_Size);
		memmove(m_Data, _Data, _Size);
		m_Size = _Size;

		AllocateComponent Allocate = { ResourceType::IndexBuffer };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	const uint32& IndexBuffer::GetCount() const
	{
		return m_Count;
	}

	void IndexBuffer::SetData(const void* _Data, const uint32& _Size)
	{
	}

	void IndexBuffer::Bind()
	{
		m_Table.Call("Bind");
	}

	void IndexBuffer::Unbind()
	{
		m_Table.Call("Unbind");
	}

}