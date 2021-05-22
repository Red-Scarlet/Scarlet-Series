#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALBuffer : public AudioFX::AudioBuffer
	{
	public:
		OpenALBuffer(const String& _Name);
		~OpenALBuffer();

	private:

	};


}