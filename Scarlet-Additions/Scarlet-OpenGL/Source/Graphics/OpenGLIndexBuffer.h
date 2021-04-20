// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLIndexBuffer.h 03/04/2021 - Functional Class.
#pragma once

#define SCARLET_INTERFACE_BUILD_DLL
#include <ScarletInterface.h>

namespace OpenGL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenGLIndexBuffer
	{
	public:
		friend class OpenGLVertexArray;

	public:
		OpenGLIndexBuffer(const Vector<uint32>& _Indices);
		OpenGLIndexBuffer(uint32* _Indices, const uint32& _Count);
		virtual ~OpenGLIndexBuffer();

		const uint32& GetCount() const { return m_Count; }

		void Bind() const;
		void Unbind() const;

	private:
		uint32 m_RendererID;
		uint32 m_Count;

	public:
		static Ref<OpenGLIndexBuffer> Create(const Vector<uint32>& _Indices)
		{ return CreateRef<OpenGLIndexBuffer>(_Indices); }

		static Ref<OpenGLIndexBuffer> Create(uint32* _Indices, const uint32& _Count)
		{ return CreateRef<OpenGLIndexBuffer>(_Indices, _Count); }

	};

}