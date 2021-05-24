#include "AudioSource.h"

namespace AudioFX {

	Ref<CallbackTable<AudioSource>> AudioSource::s_Callback = CallbackTable<AudioSource>::Create();

	void AudioSource::PushWrapper(const CallbackWrapper<AudioSource>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<AudioSource> AudioSource::Create(const Mathematics::Transform& _Transform)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Transform);
	}

}