// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLIndexBuffer.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <ScarletRenderer.h>

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLIndexBuffer : public Renderer::IndexBuffer
	{
	public:
		friend class OpenGLVertexArray;

	public:
		OpenGLIndexBuffer(const uint32& _Size);
		OpenGLIndexBuffer(uint32* _Indices, const uint32& _Size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const uint32& GetCount() const override;


	private:
		uint32 m_RendererID;
		uint32 m_Count;
	};

}