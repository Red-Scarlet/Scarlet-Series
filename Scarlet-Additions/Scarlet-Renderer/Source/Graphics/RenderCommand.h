// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RenderCommand.h 15/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Core/CallbackTable.h"

#include "Graphics/VertexArray.h"

namespace Renderer {

	using namespace ScarletInterface;

	enum class RendererEnableFlag : uint8
	{
		RendererNone = 0x00,
		RendererBlend = 0x01,
		RendererDepthTest = 0x02,
	};

	enum class RendererClearFlag : uint8
	{
		RendererNone = 0x00,
		RendererColor = 0x01,
		RendererDepth = 0x02,
		RendererStencil = 0x04
	};

	enum class RendererPolygonFlag : uint8
	{
		RendererNone = 0x00,
		RendererPoint = 0x01,
		RendererLine = 0x02,
		RendererFill = 0x04
	};

	enum class RendererDrawingFlag : uint8
	{
		RendererNone = 0x00,
		RendererPoints = 0x01,
		RendererLines = 0x02,
		RendererTriangles = 0x04
	};

	class SCARLET_INTERFACE_API RenderCommand
	{
	public:
		friend class InterfaceRenderer;
		friend class InterfaceAllocator;

	public:
		RenderCommand();
		~RenderCommand();

		void Enable(const RendererEnableFlag& _Flag);
		void Disable(const RendererEnableFlag& _Flag);

		void SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height);
		void SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A);
		void SetClearBuffer(const RendererClearFlag& _Flag);
		void SetPolygonMode(const RendererPolygonFlag& _Flag);

		void DrawArrays(Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount = 0);
		void DrawElements(Event& _Event, const RendererDrawingFlag& _Flag, const VertexArray& _VertexArray, const uint32& _IndexCount = 0);

		bool Ready() { return m_Interface != uint64_max && !m_Table.Empty(); }
		const Interface& GetInterface() const { return m_Interface; }

	private:
		Interface m_Interface = uint64_max;
		CallbackTable m_Table;
	};

}