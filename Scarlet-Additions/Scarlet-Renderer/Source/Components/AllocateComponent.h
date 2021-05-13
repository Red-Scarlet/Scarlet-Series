// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// AllocateComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "Core/RendererContext.h"

namespace Renderer {

	using namespace ScarletInterface;

	enum class ResourceType
	{
		None = 0, Shader, VertexArray, VertexBuffer, IndexBuffer, TextureBuffer, UniformBuffer, FrameBuffer
	};

	struct AllocateComponent
	{
	public:
		ResourceType Type;
		AnyData Data;

		AllocateComponent() = default;
		AllocateComponent(const AllocateComponent&) = default;
		AllocateComponent(const ResourceType& _Type)
		{
			Type = _Type;
			Data = nullptr;
		}
	};

}