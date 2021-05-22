#include "AudioListener.h"

namespace AudioFX {

	Ref<AudioListener> AudioListener::Create(const String& _Name)
	{
		if (AudioListenerCallback->Empty()) return nullptr;
		return AudioListenerCallback->Create(_Name);
	}

}