#pragma once

#include "Core/Common.h"

#include "Events/Event.h"
#include "Utilities/Timestep.h"

namespace ScarletInterface {

	#define AppStop uint16(0x00)
	#define AppUpdate uint16(0x01)
	#define EventCategoryApplication uint16(0x01)

	class SCARLET_INTERFACE_API AppStopEvent : public Event
	{
	public:
		AppStopEvent() = default;

		EVENT_CLASS_TYPE(AppStop)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class SCARLET_INTERFACE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent(const Timestep& _Timestep)
			: m_Timestep(_Timestep)
		{
		}

		const Timestep& GetTimestep() const { return m_Timestep; }

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		Timestep m_Timestep;
	};

}