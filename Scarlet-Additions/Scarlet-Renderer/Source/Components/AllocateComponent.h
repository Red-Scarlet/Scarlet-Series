// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// AllocateComponent.h 10/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "Core/RendererContext.h"

namespace Renderer {

	using namespace ScarletInterface;

	using ResourceData = Tuple<void*, uint32>;

	enum class ResourceType
	{
		None = 0, RenderCommand, Shader, VertexArray, VertexBuffer, IndexBuffer, TextureBuffer, UniformBuffer, FrameBuffer
	};

	struct AllocateComponent
	{
	public:
		ResourceType Type;
		AnyData Resource;

		AllocateComponent() = default;
		AllocateComponent(const AllocateComponent&) = default;
		AllocateComponent(const ResourceType& _Type)
		{
			Type = _Type;
			Resource = nullptr;
		}
	};

}