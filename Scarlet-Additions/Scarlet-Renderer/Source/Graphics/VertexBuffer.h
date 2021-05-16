// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// VertexBuffer.h 13/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Core/CallbackTable.h"

#include "BufferLayout.h"

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API VertexBuffer
	{
	public:
		friend class InterfaceRenderer;
		friend class InterfaceAllocator;

	public:
		VertexBuffer(const uint32& _Size);
		VertexBuffer(float32* _Data, const uint32& _Size);
		~VertexBuffer();

		void SetData(const void* _Data, const uint32& _Size);
		void SetLayout(const BufferLayout& _Layout);

		void Bind();
		void Unbind();

		bool Ready() { return m_Interface != uint64_max && !m_Table.Empty(); }
		const Interface& GetInterface() const { return m_Interface; }

	private:
		Interface m_Interface = uint64_max;
		CallbackTable m_Table;

		void* m_Data = nullptr;
		uint32 m_Size = 0;
	};

}