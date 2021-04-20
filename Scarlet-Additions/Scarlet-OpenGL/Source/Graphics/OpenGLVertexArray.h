// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexArray.h 03/04/2021 - Functional Class.
#pragma once

#define SCARLET_INTERFACE_BUILD_DLL
#include <ScarletInterface.h>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLVertexArray
	{
	public:
		friend class OpenGLCommand;

	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void AddVertexBuffer(const Ref<OpenGLVertexBuffer>& _VertexBuffer);
		void SetIndexBuffer(const Ref<OpenGLIndexBuffer>& _IndexBuffer);

		void Bind() const;
		void Unbind() const;

	private:
		uint32 m_RendererID;
		uint32 m_VertexBufferIndex = 0;

		Vector<Ref<OpenGLVertexBuffer>> m_VertexBuffer;
		Ref<OpenGLIndexBuffer> m_IndexBuffer;

	public:
		static Ref<OpenGLVertexArray> Create()
		{ return CreateRef<OpenGLVertexArray>(); }

	};

}