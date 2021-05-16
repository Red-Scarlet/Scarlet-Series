// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLIndexBuffer.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLIndexBuffer
	{
	public:
		friend class OpenGLVertexArray;

	public:
		OpenGLIndexBuffer(const uint32& _Size, const uint32& _Count);
		OpenGLIndexBuffer(uint32* _Indices, const uint32& _Size, const uint32& _Count);
		virtual ~OpenGLIndexBuffer();

		const uint32& GetCount() const { return m_Count; }

		void Bind();
		void Unbind();

	private:
		uint32 m_RendererID;
		uint32 m_Count;

	public:
		static Ref<OpenGLIndexBuffer> Create(const uint32& _Size, const uint32& _Count)
		{ return CreateRef<OpenGLIndexBuffer>(_Size, _Count); }

		static Ref<OpenGLIndexBuffer> Create(uint32* _Indices, const uint32& _Size, const uint32& _Count)
		{ return CreateRef<OpenGLIndexBuffer>(_Indices, _Size, _Count); }

	};

}