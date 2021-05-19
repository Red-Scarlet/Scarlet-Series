// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexBuffer.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <ScarletRenderer.h>

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLVertexBuffer : public Renderer::VertexBuffer
	{
	public:
		friend class OpenGLVertexArray;

	public:
		OpenGLVertexBuffer(const uint32& _Size);
		OpenGLVertexBuffer(float32* _Vertices, const uint32& _Size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const Renderer::BufferLayout& GetLayout() const override;
		virtual void SetLayout(const Renderer::BufferLayout& _Layout) override;
		virtual void SetData(const void* _Data, const uint32& _Size) override;

	private:
		uint32 m_RendererID;
		Renderer::BufferLayout m_Layout;
	};

}