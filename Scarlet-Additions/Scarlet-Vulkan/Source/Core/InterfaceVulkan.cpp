// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceVulkan.h"

#include <Events/InterfaceEvent.h>
#include "Components/VulkanComponent.h"

namespace Vulkan {

	void InterfaceVulkan::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<VulkanComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<VulkanComponent>({});
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceVulkan::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfaceVulkan::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}