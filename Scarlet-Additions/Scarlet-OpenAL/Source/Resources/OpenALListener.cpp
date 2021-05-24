#include "OpenALListener.h"
#include <AL/al.h>

namespace OpenAL {

	OpenALListener::OpenALListener(const Mathematics::Transform& _Transform)
		: m_Transform(_Transform), m_Gain(1.0f)
	{
		SetPosition(m_Transform.Translation);
		SetOrientation(m_Transform.Rotation);
		SetVelocity(m_Transform.Scale);
		SetGain(m_Gain);
	}

	OpenALListener::~OpenALListener()
	{
	}

	void OpenALListener::SetPosition(const Mathematics::Vector3& _Position)
	{
		m_Transform.Translation = _Position;
		ALfloat listenerPos[] = { m_Transform.Translation.x, m_Transform.Translation.y, m_Transform.Translation.z };
		alListenerfv(AL_POSITION, listenerPos);
	}

	void OpenALListener::SetVelocity(const Mathematics::Vector3& _Velocity)
	{
		m_Transform.Scale = _Velocity;
		ALfloat listenerVel[] = { m_Transform.Scale.x, m_Transform.Scale.y, m_Transform.Scale.z };
		alListenerfv(AL_VELOCITY, listenerVel);
	}

	void OpenALListener::SetOrientation(const Mathematics::Vector3& _Orientation)
	{
		m_Transform.Rotation = _Orientation;
		ALfloat listenerOri[] = { 0.0,0.0,-1.0, 0.0,1.0,0.0 };
		//ALfloat listenerOri[] = { m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z };
		alListenerfv(AL_ORIENTATION, listenerOri);
	}

	void OpenALListener::SetGain(const float32& _Gain)
	{
		m_Gain = _Gain;
		alListenerf(AL_GAIN, m_Gain);
	}
}