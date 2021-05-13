// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLContext.cpp 03/04/2021 - Functional Class.
#include "OpenGLContext.h"

#include <glad/glad.h>

namespace OpenGL {

	OpenGLContext::OpenGLContext(void* _ProcAddress)
	{
		ScarletInterface::int32 status = 0;
		if (_ProcAddress == nullptr)
			status = gladLoadGL();
		else status = gladLoadGLLoader((GLADloadproc)_ProcAddress);

		if(status == -1) std::cout << "Failed to initialize OpenGL context" << std::endl;
	}

	OpenGLContext::~OpenGLContext()
	{
	}

}