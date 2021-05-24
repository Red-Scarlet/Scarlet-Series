// Copyright 2016-2021 Scarlet-GLFW / Red-Scarlet. All rights reserved.
// WindowEvent.h 03/04/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <sstream>

namespace Window {

	using namespace ScarletInterface;

	#define WindowResize uint16(0x01)
	#define WindowClose uint16(0x02)
	#define EventCategoryWindow uint16(0x00)

	class SCARLET_INTERFACE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32 width, uint32 height)
			: m_Width(width), m_Height(height) 
		{
		}

		const uint32& GetWidth() const { return m_Width; }
		const uint32& GetHeight() const { return m_Height; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize) 
		EVENT_CLASS_CATEGORY(EventCategoryWindow)

	private:
		uint32 m_Width, m_Height;

	};

	class SCARLET_INTERFACE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose) 
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};
}