#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioDevice
	{
	public:
		virtual ~AudioDevice() = default;

		virtual void Play(const uint32& _SourceHandle) = 0;

	private:
		static Ref<CallbackTable<AudioDevice>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<AudioDevice>& _Wrapper);
		static Ref<AudioDevice> Create(const String& _Name);
	};
}