// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

namespace Window {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API WindowComponent
	{
	public:
		WindowComponent() = default;
		WindowComponent(const WindowComponent&) = default;
	};

}