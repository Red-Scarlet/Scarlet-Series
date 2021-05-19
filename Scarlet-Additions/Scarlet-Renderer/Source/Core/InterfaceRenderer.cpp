// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceRenderer.h"

#include <Events/InterfaceEvent.h>
#include "Components/RendererComponent.h"

namespace Renderer {

	void InterfaceRenderer::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<RendererComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<RendererComponent>({});
			_Event.Proceed(_Event);

			m_Initialized = true, m_Running = true;
		}

	}
}