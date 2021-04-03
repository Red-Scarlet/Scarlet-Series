#pragma once

#include "Core/Common.h"

namespace ScarletInterface {

	//enum class EventType
	//{
	//	None = 0,
	//	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	//	AppTick, AppUpdate, AppRender,
	//	KeyPressed, KeyReleased, KeyTyped,
	//	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	//};
	//enum EventCategory
	//{
	//	None = 0,
	//	EventCategoryApplication		= BIT(0),
	//	EventCategoryInput				= BIT(1),
	//	EventCategoryKeyboard			= BIT(2),
	//	EventCategoryMouse				= BIT(4),
	//	EventCategoryMouseButton		= BIT(4),
	//};

	typedef uint16 EventType;
	typedef uint16 EventCategory;

	#define EVENT_CLASS_TYPE(Type) \
	static EventType GetStaticType() { return Type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #Type; }
	
	#define EVENT_CLASS_CATEGORY(Category) \
	virtual uint16 GetCategoryFlags() const override { return Category; }

	class Event
	{
	public:
		virtual ~Event() = default;
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual uint16 GetCategoryFlags() const = 0;
		virtual String ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{ return GetCategoryFlags() & category; }
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}