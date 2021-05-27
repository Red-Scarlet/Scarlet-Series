// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "Core/ImGuiInstance.h"

namespace ScarletImGui {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API ImGuiComponent
	{
	public:
		Ref<ImGuiInstance> Instance = nullptr;
		String WindowAPI = "None", RendererAPI = "None";
		bool Initialized = false;

		ImGuiComponent() = default;
		ImGuiComponent(const ImGuiComponent&) = default;
		ImGuiComponent(const Ref<ImGuiInstance>& _Instance)
			: Instance(_Instance)
		{
		}
	};

}