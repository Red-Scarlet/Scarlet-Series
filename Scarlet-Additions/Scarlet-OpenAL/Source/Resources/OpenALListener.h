#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALListener : public AudioFX::AudioListener
	{
	public:
		OpenALListener(const String& _Name);
		~OpenALListener();

	private:

	};


}