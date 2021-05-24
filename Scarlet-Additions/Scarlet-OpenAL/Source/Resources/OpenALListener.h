#pragma once

#include <ScarletInterface.h>
#include <ScarletAudioFX.h>

namespace OpenAL {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API OpenALListener : public AudioFX::AudioListener
	{
	public:
		OpenALListener(const Mathematics::Transform& _Transform);
		~OpenALListener();

		virtual void SetPosition(const Mathematics::Vector3& _Position) override;
		virtual void SetVelocity(const Mathematics::Vector3& _Velocity) override;
		virtual void SetOrientation(const Mathematics::Vector3& _Orientation) override;
		virtual void SetGain(const float32& _Gain) override;

	private:
		Mathematics::Transform m_Transform;
		float32 m_Gain;
	};


}