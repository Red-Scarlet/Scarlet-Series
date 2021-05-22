// Copyright 2016-2021 Scarlet-AudioFX / Red-Scarlet. All rights reserved.
// AudioFXComponent.h 08/04/2021 - Component Struct.
#pragma once
#include <ScarletInterface.h>
#include "Core/OpenALContext.h"

namespace OpenAL {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API OpenALComponent
	{
	public:
		OpenALComponent() = default;
		OpenALComponent(const OpenALComponent&) = default;
	};

}