#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

#include <AL/al.h>
#include "alhelpers.h"

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALDevice : public AudioFX::AudioDevice
	{
	public:
		OpenALDevice(const String& _Name);
		~OpenALDevice();

		virtual void Play(const uint32& _SourceHandle) override;

	private:
		ALCdevice* m_Device = nullptr;
	};


}