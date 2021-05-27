// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "Core/ImGuiInstance.h"

namespace ScarletOpenGLImGui {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API OpenGLImGuiComponent
	{
	public:
		OpenGLImGuiComponent() = default;
		OpenGLImGuiComponent(const OpenGLImGuiComponent&) = default;
	};

}