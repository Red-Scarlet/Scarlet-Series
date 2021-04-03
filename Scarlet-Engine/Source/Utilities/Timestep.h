#pragma once

#include "Core/Common.h"

namespace Scarlet {

	class Timestep
	{
	public:
		Timestep(float32 _Time = 0.0f)
			: m_Time(_Time)
		{
		}

		float32 GetSeconds() const { return m_Time; }
		float32 GetMilliseconds() const { return m_Time * 1000; }
		operator float32() const { return m_Time; }

	private:
		float32 m_Time;
	};

}