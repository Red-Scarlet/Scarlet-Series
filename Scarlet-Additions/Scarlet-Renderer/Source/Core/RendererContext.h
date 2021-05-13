// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// RendererContext.h 10/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API RendererContext
	{
	public:
		enum class API { None = 0, OpenGL = 1, Vulkan = 2, Dx12 = 3 };

	public:
		RendererContext(const API& _API);
		virtual ~RendererContext() = default;

		void SetAPI(const API& _API) { m_API = _API; }
		API GetAPI() { return m_API; }

	private:
		API m_API;

	public:
		static Ref<RendererContext> Create(const API& _API = API::None)
		{ return CreateRef<RendererContext>(_API); }
	};

}