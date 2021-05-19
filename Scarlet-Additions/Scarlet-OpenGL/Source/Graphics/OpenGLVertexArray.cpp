// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexArray.cpp 03/04/2021 - Functional Class.
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace OpenGL {

	static GLenum ShaderDataTypeToOpenGLBaseType(const Renderer::VertexAttributeTypes& _Type)
	{
		switch (_Type)
		{
			case Renderer::VertexAttributeTypes::Float:		return GL_FLOAT;
			case Renderer::VertexAttributeTypes::Float2:	return GL_FLOAT;
			case Renderer::VertexAttributeTypes::Float3:	return GL_FLOAT;
			case Renderer::VertexAttributeTypes::Float4:	return GL_FLOAT;
			case Renderer::VertexAttributeTypes::Mat3:		return GL_FLOAT;
			case Renderer::VertexAttributeTypes::Mat4:		return GL_FLOAT;
			case Renderer::VertexAttributeTypes::Int:		return GL_INT;
			case Renderer::VertexAttributeTypes::Int2:		return GL_INT;
			case Renderer::VertexAttributeTypes::Int3:		return GL_INT;
			case Renderer::VertexAttributeTypes::Int4:		return GL_INT;
			case Renderer::VertexAttributeTypes::Bool:		return GL_BOOL;
		}

		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray(const String& _Name)
		: m_Name(_Name)
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<Renderer::VertexBuffer>& _VertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		_VertexBuffer->Bind();

		uint32 index = 0;
		auto layout = _VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case Renderer::VertexAttributeTypes::Float:
			case Renderer::VertexAttributeTypes::Float2:
			case Renderer::VertexAttributeTypes::Float3:
			case Renderer::VertexAttributeTypes::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case Renderer::VertexAttributeTypes::Int:
			case Renderer::VertexAttributeTypes::Int2:
			case Renderer::VertexAttributeTypes::Int3:
			case Renderer::VertexAttributeTypes::Int4:
			case Renderer::VertexAttributeTypes::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case Renderer::VertexAttributeTypes::Mat3:
			case Renderer::VertexAttributeTypes::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				SCARLET_INTERFACE_ASSERT(false, "Unknown VertexAttributeTypes!");
			}
		}
		m_VertexBuffer.push_back(_VertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<Renderer::IndexBuffer>& _IndexBuffer)
	{
		glBindVertexArray(m_RendererID);
		_IndexBuffer->Bind();

		m_IndexBuffer = _IndexBuffer;
	}

	Ref<Renderer::VertexBuffer> OpenGLVertexArray::GetVertexBuffer(const uint32& _Index)
	{
		return m_VertexBuffer.at(_Index);
	}

	Ref<Renderer::IndexBuffer> OpenGLVertexArray::GetIndexBuffer()
	{
		return m_IndexBuffer;
	}

}