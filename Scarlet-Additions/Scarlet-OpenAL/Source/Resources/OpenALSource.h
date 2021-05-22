#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALSource : public AudioFX::AudioSource
	{
	public:
		OpenALSource(const String& _Name);
		~OpenALSource();

	private:

	};

}