// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceEditor.h"

#include <Events/InterfaceEvent.h>
#include "Components/EditorComponent.h"

namespace Editor {

	void InterfaceEditor::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<EditorComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<EditorComponent>({});
			_Event.Proceed(_Event);

			// Setup ImGUI Dependent on what API is USED! 
			// Required Window-API Abstraction.
			{

			}

			m_Initialized = true, m_Running = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceEditor::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfaceEditor::OnAppUpdate(AppUpdateEvent& _Event)
	{
		if (m_Running)
		{

		}

		return true;
	}
}