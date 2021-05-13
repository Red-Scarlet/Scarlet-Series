// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceAllocator.h 10/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include "Components/RendererComponent.h"

namespace Renderer {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API InterfaceAllocator : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;

	private:
		bool m_Running = false, m_Initialized = false;
		RendererContext::API m_API;
	};

}