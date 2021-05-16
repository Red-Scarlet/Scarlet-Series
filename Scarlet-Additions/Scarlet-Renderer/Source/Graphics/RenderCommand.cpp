#include "RenderCommand.h"

#include "Components/AllocateComponent.h"
#include "Core/ResourceQueue.h"

namespace Renderer {

	RenderCommand::RenderCommand()
	{
		AllocateComponent Allocate = { ResourceType::RenderCommand };
		Allocate.Resource = this;

		ResourceQueue::GetInstance()->Push(Allocate);
	}

	RenderCommand::~RenderCommand()
	{
	}

	void RenderCommand::Enable(const RendererEnableFlag& _Flag)
	{
		m_Table.Call("Enable", _Flag);
	}

	void RenderCommand::Disable(const RendererEnableFlag& _Flag)
	{
		m_Table.Call("Disable", _Flag);
	}

	void RenderCommand::SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height)
	{
		m_Table.Call("SetViewport", _X, _Y, _Width, _Height);
	}

	void RenderCommand::SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A)
	{
		m_Table.Call("SetClearColor", _R, _G, _B, _A);
	}

	void RenderCommand::SetClearBuffer(const RendererClearFlag& _Flag)
	{
		m_Table.Call("SetClearBuffer", _Flag);
	}

	void RenderCommand::SetPolygonMode(const RendererPolygonFlag& _Flag)
	{
		m_Table.Call("SetPolygonMode", _Flag);
	}

	void RenderCommand::DrawArrays(Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount)
	{
		m_Table.Call("DrawArrays", _Event, _Flag, _VertexArray, _IndexCount);
	}

	void RenderCommand::DrawElements(Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount)
	{
		m_Table.Call("DrawElements", _Event, _Flag, _VertexArray, _IndexCount);
	}

}