#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioSource
	{
	public:
		virtual ~AudioSource() = default;

	public:
		static Ref<AudioSource> Create(const String& _Name);
	};

	static Ref<CallbackTable<AudioSource>> AudioSourceCallback;

}