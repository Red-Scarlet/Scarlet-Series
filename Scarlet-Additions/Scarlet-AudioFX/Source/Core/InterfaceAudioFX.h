// Copyright 2016-2021 Scarlet-OpenGL / Red-Scarlet. All rights reserved.
// InterfaceAFX.h 02/04/2021 - Interface Class.
#pragma once

#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API InterfaceAudioFX : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;

		bool OnAppUpdate(AppUpdateEvent& _Event);

	private:
		bool m_Running = false, m_Initialized = false;
	
	};

}

INTERFACE_ENTRYPOINT(AudioFX::InterfaceAudioFX);