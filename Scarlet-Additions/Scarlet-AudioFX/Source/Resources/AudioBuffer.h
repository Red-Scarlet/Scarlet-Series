#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioBuffer
	{
	public:
		virtual ~AudioBuffer() = default;

		virtual void Bind(const uint32_t& _SourceHandle) = 0;

	private:
		static Ref<CallbackTable<AudioBuffer>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<AudioBuffer>& _Wrapper);
		static Ref<AudioBuffer> Create(const String& _Filepath);
	};


}