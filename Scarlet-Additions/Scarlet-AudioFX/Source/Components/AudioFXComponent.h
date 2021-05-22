// Copyright 2016-2021 Scarlet-AudioFX / Red-Scarlet. All rights reserved.
// AudioFXComponent.h 08/04/2021 - Component Struct.
#pragma once
#include <ScarletInterface.h>

namespace AudioFX {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API AudioFXComponent
	{
	public:
		AudioFXComponent() = default;
		AudioFXComponent(const AudioFXComponent&) = default;
	};

}