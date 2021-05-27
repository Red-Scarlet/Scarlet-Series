// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfacePhysics.h"

#include <Events/InterfaceEvent.h>
#include "Components/PhysicsComponent.h"

namespace Physics {

	void InterfacePhysics::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<PhysicsComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<PhysicsComponent>({});
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfacePhysics::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfacePhysics::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}