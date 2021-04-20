#pragma once

#include "Core/Common.h"

namespace ScarletInterface {

	typedef uint16 EventType;
	typedef uint16 EventCategory;

	#define EVENT_CLASS_TYPE(Type) \
	static EventType GetStaticType() { return Type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #Type; }
	
	#define EVENT_CLASS_CATEGORY(Category) \
	virtual uint16 GetCategoryFlags() const override { return Category; }

	class SCARLET_INTERFACE_API Event
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

		template<typename T>
		T* SetNext(T* _Event) { m_Event = _Event; return dynamic_cast<T*>(m_Event); }
		Event* GetNext() const { return m_Event; }

		void ResetEvent() { delete m_Event; m_Event = nullptr; }

	private:
		Event* m_Event = nullptr;

	};

	class SCARLET_INTERFACE_API EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

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