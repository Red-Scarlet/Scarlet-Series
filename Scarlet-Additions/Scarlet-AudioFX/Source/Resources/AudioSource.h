#pragma once

#include <ScarletInterface.h>

namespace AudioFX {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API AudioSource
	{
	public:
		virtual ~AudioSource() = default;

		virtual void SetPosition(const Mathematics::Vector3& _Position) = 0;
		virtual void SetVelocity(const Mathematics::Vector3& _Velocity) = 0;
		virtual void SetDirection(const Mathematics::Vector3& _Orientation) = 0;
		virtual void SetGain(const float32& _Gain) = 0;
		virtual void SetPitch(const float32& _Pitch) = 0;
		virtual void SetLoop(const bool& _Value) = 0;
		virtual void SetSpatial(const bool& _Value) = 0;

		virtual const uint32& GetHandle() const = 0;

	private:
		static Ref<CallbackTable<AudioSource>> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper<AudioSource>& _Wrapper);
		static Ref<AudioSource> Create(const Mathematics::Transform& _Transform);
	};

}