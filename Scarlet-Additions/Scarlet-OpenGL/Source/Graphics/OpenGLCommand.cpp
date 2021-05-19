// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLCommand.cpp 03/04/2021 - Functional Class.
#include "OpenGLCommand.h"

#include <glad/glad.h>

namespace OpenGL {

	OpenGLCommand::OpenGLCommand(const String& _Name)
		: m_Name(_Name)
	{
	}

	void OpenGLCommand::Enable(const Renderer::RendererEnableFlag& _Flag)
	{
		if ((uint8)_Flag & (uint8)Renderer::RendererEnableFlag::RendererBlend) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		if ((uint8)_Flag & (uint8)Renderer::RendererEnableFlag::RendererDepthTest)
			glEnable(GL_DEPTH_TEST);
	}

	void OpenGLCommand::Disable(const Renderer::RendererEnableFlag& _Flag)
	{
		if ((uint8)_Flag & (uint8)Renderer::RendererEnableFlag::RendererBlend)
			glDisable(GL_BLEND);
		if ((uint8)_Flag & (uint8)Renderer::RendererEnableFlag::RendererDepthTest)
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLCommand::SetViewport(const uint32& _X, const uint32& _Y, const uint32& _Width, const uint32& _Height)
	{
		glViewport(_X, _Y, _Width, _Height);
	}

	void OpenGLCommand::SetClearColor(const float32& _R, const float32& _G, const float32& _B, const float32& _A)
	{
		glClearColor(_R, _G, _B, _A);
	}

	void OpenGLCommand::SetClearBuffer(const Renderer::RendererClearFlag& _Flag)
	{
		GLenum mode = {};

		if ((uint8)_Flag & (uint8)Renderer::RendererClearFlag::RendererColor)
			mode |= GL_COLOR_BUFFER_BIT;
		if ((uint8)_Flag & (uint8)Renderer::RendererClearFlag::RendererDepth)
			mode |= GL_DEPTH_BUFFER_BIT;
		if ((uint8)_Flag & (uint8)Renderer::RendererClearFlag::RendererStencil)
			mode |= GL_STENCIL_BUFFER_BIT;

		glClear(mode);
	}

	void OpenGLCommand::SetPolygonMode(const Renderer::RendererPolygonFlag& _Flag)
	{
		if ((uint8)_Flag & (uint8)Renderer::RendererPolygonFlag::RendererPoint)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		if ((uint8)_Flag & (uint8)Renderer::RendererPolygonFlag::RendererLine)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if ((uint8)_Flag & (uint8)Renderer::RendererPolygonFlag::RendererFill)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLCommand::DrawArrays(const Renderer::RendererDrawingFlag& _Flag, const Ref<Renderer::VertexArray>& _VertexArray, const uint32& _IndexCount)
	{
		GLenum mode = {};

		if ((uint8)_Flag & (uint8)Renderer::RendererDrawingFlag::RendererPoints)
			mode = GL_POINTS;
		if ((uint8)_Flag & (uint8)Renderer::RendererDrawingFlag::RendererLines)
			mode = GL_LINES;
		if ((uint8)_Flag & (uint8)Renderer::RendererDrawingFlag::RendererTriangles)
			mode = GL_TRIANGLES;

		glDrawArrays(mode, GL_UNSIGNED_INT, 3);
	}

	void OpenGLCommand::DrawElements(const Renderer::RendererDrawingFlag& _Flag, const Ref<Renderer::VertexArray>& _VertexArray, const uint32& _IndexCount)
	{
		GLenum mode = {};

		if ((uint8)_Flag & (uint8)Renderer::RendererDrawingFlag::RendererPoints)
			mode = GL_POINTS;
		if ((uint8)_Flag & (uint8)Renderer::RendererDrawingFlag::RendererLines)
			mode = GL_LINES;
		if ((uint8)_Flag & (uint8)Renderer::RendererDrawingFlag::RendererTriangles)
			mode = GL_TRIANGLES;

		uint32 count = _IndexCount == 0 ? _VertexArray->GetIndexBuffer()->GetCount() : _IndexCount;
		glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
	}

}