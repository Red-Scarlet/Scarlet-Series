#pragma once

#include "Core/Common.h"
#include <iostream>

//#include "Core/ComponentManager.h"

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
		using EventCallbackFn = std::function<bool(Event&)>;

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
		T* Push(T* _Event) { m_Events.push_back(_Event); return dynamic_cast<T*>(m_Events.back()); }
		Event* Back() { return m_Events.back(); }
		void Pop() { delete m_Events.back(); m_Events.pop_back(); }
		bool Empty() { return m_Events.empty(); }
		uint32 Count() { return m_Events.size(); }

		void SetCallback(const EventCallbackFn& _Callback)
		{ m_Callback = _Callback; m_CallbackSet = true; }

		bool Proceed(Event& _Event)
		{
			if (m_CallbackSet == false) return false;

			return m_Callback(_Event);
		}
		
		bool HasCallback() { return m_CallbackSet; }

	private:
		Vector<Event*> m_Events;
		EventCallbackFn m_Callback;
		bool m_CallbackSet = false;
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
				return m_Event.Handled |= func(static_cast<T&>(m_Event));
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