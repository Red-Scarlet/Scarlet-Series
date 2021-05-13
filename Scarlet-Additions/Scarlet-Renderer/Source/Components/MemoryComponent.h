// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// MemoryComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "Core/RendererContext.h"

namespace Renderer {

	using namespace ScarletInterface;

	struct MemoryComponent
	{
	public:
		AnyData Data;

		MemoryComponent() = default;
		MemoryComponent(const MemoryComponent&) = default;
		MemoryComponent(const AnyData& _Data)
		{
			Data = _Data;
		}
	};

}