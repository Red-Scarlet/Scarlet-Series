// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLCommand.cpp 03/04/2021 - Functional Class.
#include "OpenGLCommand.h"

#include <glad/glad.h>

namespace OpenGL {

	void OpenGLCommand::Enable(const OpenGLEnableFlag& _Flag)
	{
		if ((uint8)_Flag & (uint8)OpenGLEnableFlag::OpenGLBlend) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		if ((uint8)_Flag & (uint8)OpenGLEnableFlag::OpenGLDepthTest)
			glEnable(GL_DEPTH_TEST);
	}

	void OpenGLCommand::Disable(const OpenGLEnableFlag& _Flag)
	{
		if ((uint8)_Flag & (uint8)OpenGLEnableFlag::OpenGLBlend)
			glDisable(GL_BLEND);
		if ((uint8)_Flag & (uint8)OpenGLEnableFlag::OpenGLDepthTest)
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

	void OpenGLCommand::SetClearBuffer(const OpenGLClearFlag& _Flag)
	{
		GLenum mode = {};

		if ((uint8)_Flag & (uint8)OpenGLClearFlag::OpenGLColor)
			mode |= GL_COLOR_BUFFER_BIT;
		if ((uint8)_Flag & (uint8)OpenGLClearFlag::OpenGLDepth)
			mode |= GL_DEPTH_BUFFER_BIT;
		if ((uint8)_Flag & (uint8)OpenGLClearFlag::OpenGLStencil)
			mode |= GL_STENCIL_BUFFER_BIT;

		glClear(mode);
	}

	void OpenGLCommand::SetPolygonMode(const OpenGLPolygonFlag& _Flag)
	{
		if ((uint8)_Flag & (uint8)OpenGLPolygonFlag::OpenGLPoint)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		if ((uint8)_Flag & (uint8)OpenGLPolygonFlag::OpenGLLine)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if ((uint8)_Flag & (uint8)OpenGLPolygonFlag::OpenGLFill)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void OpenGLCommand::DrawArrays(const OpenGLDrawingFlag& _Flag, const Ref<OpenGLVertexArray>& _VertexArray, const uint32& _IndexCount)
	{
		GLenum mode = {};

		if ((uint8)_Flag & (uint8)OpenGLDrawingFlag::OpenGLPoints)
			mode = GL_POINTS;
		if ((uint8)_Flag & (uint8)OpenGLDrawingFlag::OpenGLLines)
			mode = GL_LINES;
		if ((uint8)_Flag & (uint8)OpenGLDrawingFlag::OpenGLTriangles)
			mode = GL_TRIANGLES;

		uint32 count = _IndexCount == 0 ? _VertexArray->m_IndexBuffer->GetCount() : _IndexCount;
		glDrawArrays(mode, GL_UNSIGNED_INT, count);
	}

	void OpenGLCommand::DrawElements(const OpenGLDrawingFlag& _Flag, const Ref<OpenGLVertexArray>& _VertexArray, const uint32& _IndexCount)
	{
		GLenum mode = {};

		if ((uint8)_Flag & (uint8)OpenGLDrawingFlag::OpenGLPoints)
			mode = GL_POINTS;
		if ((uint8)_Flag & (uint8)OpenGLDrawingFlag::OpenGLLines)
			mode = GL_LINES;
		if ((uint8)_Flag & (uint8)OpenGLDrawingFlag::OpenGLTriangles)
			mode = GL_TRIANGLES;

		uint32 count = _IndexCount == 0 ? _VertexArray->m_IndexBuffer->GetCount() : _IndexCount;
		glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
	}

}