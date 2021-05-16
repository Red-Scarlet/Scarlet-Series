// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLCommand.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "OpenGLVertexArray.h"

namespace OpenGL {

	using namespace ScarletInterface;
	
	enum class SCARLET_INTERFACE_API OpenGLEnableFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLBlend = 0x01,
		OpenGLDepthTest = 0x02,
	};
	
	enum class SCARLET_INTERFACE_API OpenGLClearFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLColor = 0x01,
		OpenGLDepth = 0x02,
		OpenGLStencil = 0x04
	};
	
	enum class SCARLET_INTERFACE_API OpenGLPolygonFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLPoint = 0x01,
		OpenGLLine = 0x02,
		OpenGLFill = 0x04
	};
	
	enum class SCARLET_INTERFACE_API OpenGLDrawingFlag : uint8
	{
		OpenGLNone = 0x00,
		OpenGLPoints = 0x01,
		OpenGLLines = 0x02,
		OpenGLTriangles = 0x04
	};

	class SCARLET_INTERFACE_API OpenGLCommand
	{
	public:
		OpenGLCommand();
		virtual ~OpenGLCommand() = default;

		void Enable(const OpenGLEnableFlag& _Flag);
		void Disable(const OpenGLEnableFlag& _Flag);

		void SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height);
		void SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A);
		void SetClearBuffer(const OpenGLClearFlag& _Flag);
		void SetPolygonMode(const OpenGLPolygonFlag& _Flag);

		void DrawArrays(const OpenGLDrawingFlag& _Flag, const Ref<OpenGLVertexArray>& _VertexArray, const uint32& _IndexCount = 0);
		void DrawElements(const OpenGLDrawingFlag& _Flag, const Ref<OpenGLVertexArray>& _VertexArray, const uint32& _IndexCount = 0);

		static Ref<OpenGLCommand> Create()
		{ return CreateRef<OpenGLCommand>(); }
	};

}