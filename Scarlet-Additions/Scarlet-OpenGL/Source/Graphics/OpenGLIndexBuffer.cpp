// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLIndexBuffer.h 03/04/2021 - Functional Class.
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace OpenGL {

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32& _Size, const uint32& _Count)
		: m_Count(_Count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, _Size, nullptr, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* _Indices, const uint32& _Size, const uint32& _Count)
		: m_Count(_Count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Size, _Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}