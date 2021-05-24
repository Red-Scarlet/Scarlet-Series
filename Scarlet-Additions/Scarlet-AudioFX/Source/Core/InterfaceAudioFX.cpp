// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// InterfaceGL.cpp 02/04/2021 - Interface Class.
#include "InterfaceAudioFX.h"
#include <Events/InterfaceEvent.h>

#include "Components/AudioFXComponent.h"

namespace AudioFX {

	void InterfaceAudioFX::OnGlobal(Event& _Event)
	{
		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<AudioFXComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<AudioFXComponent>({});
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceAudioFX::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	bool InterfaceAudioFX::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return m_Running;
	}
}