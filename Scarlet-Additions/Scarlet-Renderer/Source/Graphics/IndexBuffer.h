// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// IndexBuffer.h 14/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Core/CallbackTable.h"

#include "BufferLayout.h"

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API IndexBuffer
	{
	public:
		friend class InterfaceRenderer;
		friend class InterfaceAllocator;

	public:
		IndexBuffer(const uint32& _Size, const uint32& _Count);
		IndexBuffer(uint32* _Data, const uint32& _Size, const uint32& _Count);
		~IndexBuffer();

		const uint32& GetCount() const;

		void SetData(const void* _Data, const uint32& _Size);
		void Bind();
		void Unbind();

		bool Ready() { return m_Interface != uint64_max && !m_Table.Empty(); }
		const Interface& GetInterface() const { return m_Interface; }

	private:
		Interface m_Interface = uint64_max;
		CallbackTable m_Table;
		uint32_t m_Count;

		void* m_Data = nullptr;
		uint32 m_Size = 0;

	};

}