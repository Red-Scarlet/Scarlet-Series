// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "Core/RendererContext.h"

namespace Renderer {

	using namespace ScarletInterface;

	struct RendererComponent
	{
	public:
		Ref<RendererContext> Context;

		RendererComponent() = default;
		RendererComponent(const RendererComponent&) = default;
		RendererComponent(const RendererContext::API& _API)
		{
			Context = RendererContext::Create(_API);
		}
	};

}