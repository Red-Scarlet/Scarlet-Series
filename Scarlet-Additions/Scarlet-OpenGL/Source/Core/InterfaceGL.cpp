// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// InterfaceGL.cpp 02/04/2021 - Interface Class.
#include "InterfaceGL.h"
#include "Components/OpenGLComponent.h"
#include "Graphics/OpenGLCommand.h"

#include <ScarletGLFW.h>

namespace OpenGL {

	// OpenGL Commands [x]
	// OpenGL Buffers
	// OpenGL Shaders
	// OpenGL Textures
	// OpenGL Vertex Array
	// OpenGL FrameBuffers

	void InterfaceGL::OnCreate(InterfaceObject& _Interface)
	{
		this->RegisterComponent<OpenGLComponent>();

		if(!this->HasModule<GLFW::InterfaceGLFW>()) this->PushModule<GLFW::InterfaceGLFW>();
	}

	void InterfaceGL::OnDestroy(InterfaceObject& _Interface)
	{
	}

	void InterfaceGL::OnUpdate(InterfaceObject& _Interface)
	{
		this->PushSignature<InterfaceGL, GLFW::GLFWComponent>();
		{
			InterfaceObject& glfwInterface = this->GetInterfaceObject(0);
			if(glfwInterface.HasComponent<GLFW::GLFWComponent>())
			{
				if (!_Interface.HasComponent<OpenGLComponent>())
				{
					GLFW::GLFWComponent& glfwComponent = glfwInterface.GetComponent<GLFW::GLFWComponent>();
					_Interface.AddComponent<OpenGLComponent>(glfwComponent.MainContext->GetProcAddress());
				}
			}
			else {
				if (_Interface.HasComponent<OpenGLComponent>()) {
					_Interface.RemoveComponent<OpenGLComponent>();
					SCARLET_INTERFACE_ERROR("No GLFW Component Attached!");
				}
			}
		}
		this->PopSignature<InterfaceGL, GLFW::GLFWComponent>();

		if (_Interface.HasComponent<OpenGLComponent>())
		{
			OpenGLCommand::SetClearColor(0.10f, 0.10f, 0.10f, 1.00f);
			OpenGLCommand::SetClearBuffer(OpenGLClearFlag::OpenGLColor | OpenGLClearFlag::OpenGLColor);
		}
	}

	void InterfaceGL::OnEvent(Event& _Event)
	{
	}

}