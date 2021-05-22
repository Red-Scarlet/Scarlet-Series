#include "AudioDevice.h"

namespace AudioFX {

	Ref<AudioDevice> AudioDevice::Create(const String& _Name)
	{
		if (AudioDeviceCallback->Empty()) return nullptr;
		return AudioDeviceCallback->Create(_Name);
	}

}