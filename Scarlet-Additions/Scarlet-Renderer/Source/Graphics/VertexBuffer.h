// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLShader.h 04/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Core/CallbackTable.h"

class VertexBuffer;
class IndexBuffer;

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API VertexBuffer
	{
	public:
		friend class InterfaceRenderer;
		friend class InterfaceAllocator;

	public:
		VertexBuffer();
		~VertexBuffer();

		void SetData(const void* _Data, const uint32& _Size);
		void SetLayout(const BufferLayout& _Layout);

		void Bind();
		void Unbind();

	private:
		Interface m_Interface = uint64_max;
		CallbackTable m_Table;
	};

}