#include "AudioListener.h"

namespace AudioFX {

	Ref<CallbackTable<AudioListener>> AudioListener::s_Callback = CallbackTable<AudioListener>::Create();

	void AudioListener::PushWrapper(const CallbackWrapper<AudioListener>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<AudioListener> AudioListener::Create(const Mathematics::Transform& _Transform)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Transform);
	}

}