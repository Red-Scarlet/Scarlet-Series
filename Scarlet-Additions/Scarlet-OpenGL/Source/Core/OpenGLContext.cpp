// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLContext.cpp 03/04/2021 - Functional Class.
#include "OpenGLContext.h"

namespace OpenGL {

	OpenGLContext::OpenGLContext(void* _ProcAddress)
	{
		ScarletInterface::int32 status = gladLoadGLLoader((GLADloadproc)_ProcAddress);
		SCARLET_INTERFACE_ASSERT(status, "Failed to initailize Glad!");

		SCARLET_INTERFACE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		SCARLET_INTERFACE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	OpenGLContext::~OpenGLContext()
	{
	}

}