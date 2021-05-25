// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API RendererComponent
	{
	public:
		String API = "None";

		RendererComponent() = default;
		RendererComponent(const RendererComponent&) = default;
		RendererComponent(const String& _API)
			: API(_API)
		{

		}

	};

}