#pragma once

#include "Core/Common.h"
#include <ScarletInterface.h>
#include <sstream>

namespace Scarlet {

	#define AppUpdate uint16(0x01)
	#define EventCategoryApplication uint16(0x00)

	using namespace ScarletInterface;

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}