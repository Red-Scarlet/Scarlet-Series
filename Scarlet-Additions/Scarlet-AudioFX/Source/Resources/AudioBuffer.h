#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioBuffer
	{
	public:
		virtual ~AudioBuffer() = default;

	public:
		static Ref<AudioBuffer> Create(const String& _Name);
	};

	static Ref<CallbackTable<AudioBuffer>> AudioBufferCallback;

}