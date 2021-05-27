// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceDirectX.h"

#include <Events/InterfaceEvent.h>
#include "Components/DirectXComponent.h"

namespace DirectX {

	void InterfaceDirectX::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<DirectXComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<DirectXComponent>({});
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceDirectX::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfaceDirectX::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}