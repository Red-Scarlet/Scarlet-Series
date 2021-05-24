#pragma once

#include <ScarletInterface.h>
#include "CallbackTable.h"

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioListener
	{
	public:
		virtual ~AudioListener() = default;

		virtual void SetPosition(const Mathematics::Vector3& _Position) = 0;
		virtual void SetVelocity(const Mathematics::Vector3& _Velocity) = 0;
		virtual void SetOrientation(const Mathematics::Vector3& _Orientation) = 0;
		virtual void SetGain(const float32& _Gain) = 0;

	private:
		static Ref<CallbackTable<AudioListener>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<AudioListener>& _Wrapper);
		static Ref<AudioListener> Create(const Mathematics::Transform& _Transform);
	};

}