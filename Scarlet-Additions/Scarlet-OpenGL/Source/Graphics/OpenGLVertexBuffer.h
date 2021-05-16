// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLVertexBuffer.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "OpenGLBufferLayout.h"

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLVertexBuffer
	{
	public:
		friend class OpenGLVertexArray;

	public:
		OpenGLVertexBuffer(const uint32& _Size);
		OpenGLVertexBuffer(float32* _Vertices, const uint32& _Size);
		virtual ~OpenGLVertexBuffer();

		void SetData(const void* _Data, const uint32& _Size);
		void SetLayout(const OpenGLBufferLayout& _Layout);
		
		void Bind();
		void Unbind();

	private:
		uint32 m_RendererID;
		OpenGLBufferLayout m_Layout;

	public:
		static Ref<OpenGLVertexBuffer> Create(const uint32& _Size)
		{ return CreateRef<OpenGLVertexBuffer>(_Size); }

		static Ref<OpenGLVertexBuffer> Create(float32* _Vertices, const uint32& _Size)
		{ return CreateRef<OpenGLVertexBuffer>(_Vertices, _Size); }
	};

}