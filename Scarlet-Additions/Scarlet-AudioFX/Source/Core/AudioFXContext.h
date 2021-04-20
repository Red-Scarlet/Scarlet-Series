// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLContext.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>

namespace AudioFX {

	class AudioFXContext
	{
	public:
		AudioFXContext();
		~AudioFXContext();

	public:
		static ScarletInterface::Ref<AudioFXContext> Create()
		{ return ScarletInterface::CreateRef<AudioFXContext>(); }
	};

}