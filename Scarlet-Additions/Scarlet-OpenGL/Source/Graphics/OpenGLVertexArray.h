// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexArray.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <ScarletRenderer.h>

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLVertexArray : public Renderer::VertexArray
	{
	public:
		friend class OpenGLCommand;

	public:
		OpenGLVertexArray(const String& _Name);
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<Renderer::VertexBuffer>& _VertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<Renderer::IndexBuffer>& _IndexBuffer) override;

		virtual Ref<Renderer::VertexBuffer> GetVertexBuffer(const uint32& _Index = 0) override;
		virtual Ref<Renderer::IndexBuffer> GetIndexBuffer() override;

	private:
		String m_Name;
		uint32 m_RendererID;
		uint32 m_VertexBufferIndex = 0;

		Vector<Ref<Renderer::VertexBuffer>> m_VertexBuffer;
		Ref<Renderer::IndexBuffer> m_IndexBuffer;
	};

}