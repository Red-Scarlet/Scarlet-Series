// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceWindow.h"

#include <Events/InterfaceEvent.h>
#include "Components/WindowComponent.h"

namespace Window {

	void InterfaceWindow::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<WindowComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<WindowComponent>({});
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceWindow::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfaceWindow::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}