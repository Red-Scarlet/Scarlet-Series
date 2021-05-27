// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>

namespace Vulkan {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API VulkanComponent
	{
	public:
		VulkanComponent() = default;
		VulkanComponent(const VulkanComponent&) = default;
	};

}