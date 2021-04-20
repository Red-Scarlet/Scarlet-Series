// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLContext.h 03/04/2021 - Functional Class.
#pragma once

#define SCARLET_INTERFACE_BUILD_DLL
#include <ScarletInterface.h>
#include <glad/glad.h>

namespace OpenGL {

	class SCARLET_INTERFACE_API OpenGLContext
	{
	public:
		OpenGLContext(void* _ProcAddress);
		~OpenGLContext();

	public:
		static ScarletInterface::Ref<OpenGLContext> Create(void* _ProcAddress)
		{ return ScarletInterface::CreateRef<OpenGLContext>(_ProcAddress); }
	};

}