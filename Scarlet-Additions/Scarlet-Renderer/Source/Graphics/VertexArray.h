// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLShader.h 04/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Core/CallbackTable.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API VertexArray
	{
	public:
		friend class InterfaceRenderer;
		friend class InterfaceAllocator;

	public:
		VertexArray();
		~VertexArray();

		void AddVertexBuffer(const VertexBuffer& _VertexBuffer, Event& _Event);
		void SetIndexBuffer(const IndexBuffer& _IndexBuffer, Event& _Event);

		void Bind();
		void Unbind();

		bool Ready() { return m_Interface != uint64_max && !m_Table.Empty(); }
		const Interface& GetInterface() const { return m_Interface; }

	private:
		Interface m_Interface = uint64_max;
		CallbackTable m_Table;
	};

}