// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

namespace PhysX {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API PhysXComponent
	{
	public:
		PhysXComponent() = default;
		PhysXComponent(const PhysXComponent&) = default;
	};

}