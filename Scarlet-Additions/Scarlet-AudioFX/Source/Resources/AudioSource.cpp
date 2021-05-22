#include "AudioSource.h"

namespace AudioFX {

	Ref<AudioSource> AudioSource::Create(const String& _Name)
	{
		if (AudioSourceCallback->Empty()) return nullptr;
		return AudioSourceCallback->Create(_Name);
	}

}