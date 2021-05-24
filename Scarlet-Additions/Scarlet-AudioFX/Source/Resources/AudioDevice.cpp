#include "AudioDevice.h"

namespace AudioFX {

	Ref<CallbackTable<AudioDevice>> AudioDevice::s_Callback = CallbackTable<AudioDevice>::Create();

	void AudioDevice::PushWrapper(const CallbackWrapper<AudioDevice>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<AudioDevice> AudioDevice::Create(const String& _Name)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Name);
	}

}