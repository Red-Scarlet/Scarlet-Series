#include "OpenALSource.h"
#include <AL/al.h>
#include <AL/alext.h>

namespace OpenAL {

	OpenALSource::OpenALSource(const Mathematics::Transform& _Transform)
		: m_Transform(_Transform)
	{
		alGenSources(1, &m_SourceHandle);
		SetPosition(m_Transform.Translation);
		SetVelocity(m_Transform.Scale);
		SetDirection(m_Transform.Rotation);
		SetGain(m_Gain);
	}

	OpenALSource::~OpenALSource()
	{
		alDeleteSources(1, &m_SourceHandle);
	}

	void OpenALSource::SetPosition(const Mathematics::Vector3& _Position)
	{
		m_Transform.Translation = _Position;
		ALfloat position[] = { m_Transform.Translation.x, m_Transform.Translation.y, m_Transform.Translation.z };
		alSourcefv(m_SourceHandle, AL_POSITION, position);
	}

	void OpenALSource::SetVelocity(const Mathematics::Vector3& _Velocity)
	{
		m_Transform.Scale = _Velocity;
		ALfloat velocity[] = { m_Transform.Scale.x, m_Transform.Scale.y, m_Transform.Scale.z };
		alSourcefv(m_SourceHandle, AL_VELOCITY, velocity);
	}

	void OpenALSource::SetDirection(const Mathematics::Vector3& _Direction)
	{
		m_Transform.Rotation = _Direction;
		ALfloat direction[] = { m_Transform.Rotation.x, m_Transform.Rotation.y, m_Transform.Rotation.z };
		alSourcefv(m_SourceHandle, AL_DIRECTION, direction);
	}

	void OpenALSource::SetGain(const float32& _Gain)
	{
		m_Gain = _Gain;		
		alSourcef(m_SourceHandle, AL_GAIN, m_Gain);
	}

	void OpenALSource::SetPitch(const float32& _Pitch)
	{
		m_Pitch = _Pitch;		
		alSourcef(m_SourceHandle, AL_PITCH, m_Pitch);
	}

	void OpenALSource::SetLoop(const bool& _Value)
	{
		m_Loop = _Value;		
		alSourcei(m_SourceHandle, AL_LOOPING, m_Loop ? AL_TRUE : AL_FALSE);
	}

	void OpenALSource::SetSpatial(const bool& _Value)
	{
		m_Spatial = _Value;

		alSourcei(m_SourceHandle, AL_SOURCE_SPATIALIZE_SOFT, _Value ? AL_TRUE : AL_FALSE);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}

	const uint32& OpenALSource::GetHandle() const
	{
		return m_SourceHandle;
	}
}