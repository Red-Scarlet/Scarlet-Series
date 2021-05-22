#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>
#include <alc.h>
#include <al.h>

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALDevice : public AudioFX::AudioDevice
	{
	public:
		OpenALDevice(const String& _Name);
		~OpenALDevice();

	private:
		ALCdevice* m_Device;
		ALCcontext* m_Context;
	};


}