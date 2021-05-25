// Copyright 2016-2021 Scarlet-Renderer / Red-Scarlet. All rights reserved.
// InterfaceRenderer.cpp 08/04/2021 - Interface Class.
#include "InterfaceEditor.h"

#include <Events/InterfaceEvent.h>
#include "Components/EditorComponent.h"

#include <ScarletWindow.h>

namespace Editor {

	void InterfaceEditor::OnGlobal(Event& _Event)
	{
		_Event.Push(new InterfaceRequirementEvent(this))->Set({
			"Scarlet-Window",
			"Scarlet-SceneGraph",
			"Scarlet-Renderer",
			"Scarlet-AudioFX" 
		});
		if (_Event.Proceed(_Event) == false) return;

		if (!m_Initialized)
		{
			//_Event.Push(new SignaturePushEvent(this))->Bind<EditorComponent>();
			//_Event.Push(new ComponentPushEvent(this))->Bind<EditorComponent>({});
			//_Event.Proceed(_Event);

			// Setup ImGUI Dependent on what API is USED! 
			// Required Window-API Abstraction.
			{
				{
					_Event.Push(new SignaturePushEvent(this))->Bind<Window::WindowComponent>();
					_Event.Proceed(_Event);

					for (Interface i : m_Set)
					{
						Window::WindowComponent* component = {};
						_Event.Push(new ComponentComputeEvent(i))->Retrieve<Window::WindowComponent>(&component);
						_Event.Proceed(_Event);

						if (component)
						{
							if (component->API == "None") return;
							std::cout << "Window API: " << component->API << std::endl;
						}
					}

					_Event.Push(new SignaturePopEvent(this))->Bind<Window::WindowComponent>();
					_Event.Push(new SignaturePushEvent(this))->Bind<EditorComponent>();
					_Event.Proceed(_Event);
				}
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