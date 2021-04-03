// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexArray.cpp 03/04/2021 - Functional Class.
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace OpenGL {

	static const GLenum& ShaderDataTypeToOpenGLBaseType(const VertexAttributeTypes& _Type)
	{
		switch (_Type)
		{
			case VertexAttributeTypes::Float:		return GL_FLOAT;
			case VertexAttributeTypes::Float2:		return GL_FLOAT;
			case VertexAttributeTypes::Float3:		return GL_FLOAT;
			case VertexAttributeTypes::Float4:		return GL_FLOAT;
			case VertexAttributeTypes::Mat3:		return GL_FLOAT;
			case VertexAttributeTypes::Mat4:		return GL_FLOAT;
			case VertexAttributeTypes::Int:			return GL_INT;
			case VertexAttributeTypes::Int2:		return GL_INT;
			case VertexAttributeTypes::Int3:		return GL_INT;
			case VertexAttributeTypes::Int4:		return GL_INT;
			case VertexAttributeTypes::Bool:		return GL_BOOL;
		}

		SCARLET_INTERFACE_ASSERT(SCARLET_ERROR, "Unknown VertexAttributeTypes!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<OpenGLVertexBuffer>& _VertexBuffer)
	{
		SCARLET_INTERFACE_ASSERT(_VertexBuffer->m_Layout.GetElements().size(), "VertexBuffer has no Layout!");
		glBindVertexArray(m_RendererID);
		_VertexBuffer->Bind();

		uint32 index = 0;
		const auto& layout = _VertexBuffer->m_Layout;
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case VertexAttributeTypes::Float:
			case VertexAttributeTypes::Float2:
			case VertexAttributeTypes::Float3:
			case VertexAttributeTypes::Float4:
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
			case VertexAttributeTypes::Int:
			case VertexAttributeTypes::Int2:
			case VertexAttributeTypes::Int3:
			case VertexAttributeTypes::Int4:
			case VertexAttributeTypes::Bool:
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
			case VertexAttributeTypes::Mat3:
			case VertexAttributeTypes::Mat4:
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

	void OpenGLVertexArray::SetIndexBuffer(const Ref<OpenGLIndexBuffer>& _IndexBuffer)
	{
		glBindVertexArray(m_RendererID);
		_IndexBuffer->Bind();

		m_IndexBuffer = _IndexBuffer;
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}