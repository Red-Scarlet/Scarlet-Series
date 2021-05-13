// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLCommand.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "OpenGLVertexArray.h"

namespace OpenGL {

	using namespace ScarletInterface;
	
	enum class OpenGLEnableFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLBlend = 0x01,
		OpenGLDepthTest = 0x02,
	};
	
	enum class OpenGLClearFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLColor = 0x01,
		OpenGLDepth = 0x02,
		OpenGLStencil = 0x04
	};
	
	enum class OpenGLPolygonFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLPoint = 0x01,
		OpenGLLine = 0x02,
		OpenGLFill = 0x04
	};
	
	enum class OpenGLDrawingFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLPoints = 0x01,
		OpenGLLines = 0x02,
		OpenGLTriangles = 0x04
	};

	class OpenGLCommand
	{
	public:
		static void Enable(const OpenGLEnableFlag& _Flag);
		static void Disable(const OpenGLEnableFlag& _Flag);

		static void SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height);
		static void SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A);
		static void SetClearBuffer(const OpenGLClearFlag& _Flag);
		static void SetPolygonMode(const OpenGLPolygonFlag& _Flag);

		static void DrawArrays(const OpenGLDrawingFlag& _Flag, const Ref<OpenGLVertexArray>& _VertexArray, const uint32& _IndexCount = 0);
		static void DrawElements(const OpenGLDrawingFlag& _Flag, const Ref<OpenGLVertexArray>& _VertexArray, const uint32& _IndexCount = 0);
	};

}