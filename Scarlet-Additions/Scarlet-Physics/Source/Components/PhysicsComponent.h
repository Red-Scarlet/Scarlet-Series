// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

namespace Physics {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API PhysicsComponent
	{
	public:
		String API = "None";

		PhysicsComponent() = default;
		PhysicsComponent(const PhysicsComponent&) = default;
		PhysicsComponent(const String& _API)
			: API(_API)
		{

		}

	};

}