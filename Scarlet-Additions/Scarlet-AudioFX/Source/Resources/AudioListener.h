#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioListener
	{
	public:
		virtual ~AudioListener() = default;

	public:
		static Ref<AudioListener> Create(const String& _Name);
	};

	static Ref<CallbackTable<AudioListener>> AudioListenerCallback;

}