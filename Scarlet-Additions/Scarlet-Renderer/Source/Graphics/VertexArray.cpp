#include "VertexArray.h"

#include "Components/AllocateComponent.h"
#include "Core/ResourceQueue.h"

namespace Renderer {

	VertexArray::VertexArray()
	{
		AllocateComponent Allocate = { ResourceType::VertexArray };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::AddVertexBuffer(const VertexBuffer& _VertexBuffer, Event& _Event)
	{
		m_Table.Call("AddVertexBuffer", _VertexBuffer, _Event);
	}

	void VertexArray::SetIndexBuffer(const IndexBuffer& _IndexBuffer, Event& _Event)
	{
		m_Table.Call("SetIndexBuffer", _IndexBuffer, _Event);
	}

	void VertexArray::Bind()
	{
		m_Table.Call("Bind");
	}

	void VertexArray::Unbind()
	{
		m_Table.Call("Unbind");
	}

}