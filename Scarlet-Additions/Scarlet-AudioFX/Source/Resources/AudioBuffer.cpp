#include "AudioBuffer.h"

namespace AudioFX {

	Ref<CallbackTable<AudioBuffer>> AudioBuffer::s_Callback = CallbackTable<AudioBuffer>::Create();

	void AudioBuffer::PushWrapper(const CallbackWrapper<AudioBuffer>& _Wrapper)
	{
		s_Callback->Push(_Wrapper);
	}

	Ref<AudioBuffer> AudioBuffer::Create(const String& _Filepath)
	{
		if (s_Callback->Empty()) return nullptr;
		return s_Callback->Create(_Filepath);
	}

}