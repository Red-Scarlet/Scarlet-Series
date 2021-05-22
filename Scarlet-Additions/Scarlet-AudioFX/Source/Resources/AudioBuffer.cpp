#include "AudioBuffer.h"

namespace AudioFX {

	Ref<AudioBuffer> AudioBuffer::Create(const String& _Name)
	{
		if (AudioBufferCallback->Empty()) return nullptr;
		return AudioBufferCallback->Create(_Name);
	}

}