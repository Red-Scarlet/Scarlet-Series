// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.h 08/04/2021 - Interface Class.
#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	// OpenGL Interface currently uses GLFW (Abstract to Scarlet-WindowAPI)
	class InterfaceRenderer : public InterfaceModule
	{
	public:
		virtual void OnCreate(InterfaceObject& _Interface) override;
		virtual void OnDestroy(InterfaceObject& _Interface) override;
		virtual void OnUpdate(InterfaceObject& _Interface) override;
		virtual void OnEvent(Event& _Event) override;
	
	};

}