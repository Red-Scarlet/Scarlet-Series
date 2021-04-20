// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLCommand.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "VertexArray.h"

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

	class RendererCommand
	{
	public:
		static void Enable(const RendererEnableFlag& _Flag);
		static void Disable(const RendererEnableFlag& _Flag);

		static void SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height);
		static void SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A);
		static void SetClearBuffer(const RendererClearFlag& _Flag);
		static void SetPolygonMode(const RendererPolygonFlag& _Flag);

		static void DrawArrays(const RendererDrawingFlag& _Flag, const Ref<VertexArray>& _VertexArray, const uint32& _IndexCount = 0);
		static void DrawElements(const RendererDrawingFlag& _Flag, const Ref<VertexArray>& _VertexArray, const uint32& _IndexCount = 0);
	};

}