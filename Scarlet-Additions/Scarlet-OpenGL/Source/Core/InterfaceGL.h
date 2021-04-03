// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// InterfaceGL.h 02/04/2021 - Interface Class.
#pragma once

#include <ScarletInterface.h>

namespace OpenGL {

	using namespace ScarletInterface;

	// OpenGL Interface currently uses GLFW (Abstract to Scarlet-WindowAPI)
	class InterfaceGL : public InterfaceModule
	{
	public:
		virtual void OnCreate(InterfaceObject& _Interface) override;
		virtual void OnDestroy(InterfaceObject& _Interface) override;
		virtual void OnUpdate(InterfaceObject& _Interface) override;
		virtual void OnEvent(Event& _Event) override;

	private:
		Function<void(InterfaceObject&, Vector<InterfaceObject>)> m_InitializeFunction;
	};

}