#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALSource : public AudioFX::AudioSource
	{
	public:
		OpenALSource(const Mathematics::Transform& _Transform);
		~OpenALSource();

		virtual void SetPosition(const Mathematics::Vector3& _Position) override;
		virtual void SetVelocity(const Mathematics::Vector3& _Velocity) override;
		virtual void SetDirection(const Mathematics::Vector3& _Orientation) override;
		virtual void SetGain(const float32& _Gain) override;
		virtual void SetPitch(const float32& _Pitch) override;
		virtual void SetLoop(const bool& _Value) override;
		virtual void SetSpatial(const bool& _Value) override;

		virtual const uint32& GetHandle() const override;

	private:
		Mathematics::Transform m_Transform;
		float32 m_Gain = 1.0f, m_Pitch = 1.0f;
		bool m_Loop = false, m_Spatial = false;

		uint32 m_SourceHandle = 0;
	};

}