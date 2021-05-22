#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioDevice
	{
	public:
		virtual ~AudioDevice() = default;

	public:
		static Ref<AudioDevice> Create(const String& _Name);
	};

	static Ref<CallbackTable<AudioDevice>> AudioDeviceCallback;

}