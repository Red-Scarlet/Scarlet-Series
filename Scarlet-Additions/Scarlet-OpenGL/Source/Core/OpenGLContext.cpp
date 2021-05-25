// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// OpenGLContext.cpp 03/04/2021 - Functional Class.
#include "OpenGLContext.h"
#include <glad/glad.h>

namespace OpenGL {

	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

	OpenGLContext::OpenGLContext(void* _ProcAddress)
	{
		ScarletInterface::int32 status = 0;
		if (_ProcAddress == nullptr)
			status = gladLoadGL();
		else status = gladLoadGLLoader((GLADloadproc)_ProcAddress);

		if(status == -1) std::cout << "Failed to initialize OpenGL context" << std::endl;


		// During init, enable debug output
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
	}

	OpenGLContext::~OpenGLContext()
	{
	}

}