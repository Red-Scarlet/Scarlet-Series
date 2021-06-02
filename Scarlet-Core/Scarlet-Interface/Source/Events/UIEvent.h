#pragma once
#include "Core/Common.h"
#include "Core/ComponentManager.h"
#include "Core/InterfaceModule.h"
#include "Events/Event.h"

#include "UI/BasePanelUI.h"

namespace ScarletInterface {

	#define EditorPanelBind uint16(0x0400)
	#define EditorPanelDraw uint16(0x0800)
	#define EditorHook uint16(0x1000)
	#define EditorInterfaceCheck uint16(0x2000)

	#define EventCategoryEditor uint16(0x02)

	class SCARLET_INTERFACE_API EditorPanelBindEvent : public Event
	{
	public:
		EditorPanelBindEvent()
		{
		}

		void Bind(const Ref<BasePanelUI>& _UI)
		{
			m_UIComponents.push_back(_UI);
		}

		EVENT_CLASS_TYPE(EditorPanelBind)
		EVENT_CLASS_CATEGORY(EventCategoryEditor)

	public:
		Vector<Ref<BasePanelUI>> m_UIComponents;
	};

	class SCARLET_INTERFACE_API EditorPanelDrawEvent : public Event
	{
	public:
		EditorPanelDrawEvent()
		{
		}

		const uint32& GetSize() { return m_UIComponents.size(); }

		const Ref<BasePanelUI>& GetUI(const uint32& _Index)
		{
			return m_UIComponents.at(_Index);
		}

		EVENT_CLASS_TYPE(EditorPanelDraw)
		EVENT_CLASS_CATEGORY(EventCategoryEditor)

	public:
		Vector<Ref<BasePanelUI>> m_UIComponents;
	};

	class SCARLET_INTERFACE_API EditorHookEvent : public Event
	{
	public:
		using EditorCallbackFn = Function<bool(EditorPanelDrawEvent&)>;

	public:
		EditorHookEvent(InterfaceModule* _Module)
		{
			m_Module = _Module;
		}

		void Bind(const EditorCallbackFn& _Callback)
		{
			m_Callback = _Callback;
		}

		const EditorCallbackFn& GetCallback() { return m_Callback; }

		InterfaceModule* GetModule() { return m_Module; }

		EVENT_CLASS_TYPE(EditorHook)
		EVENT_CLASS_CATEGORY(EventCategoryEditor)

	private:
		InterfaceModule* m_Module = nullptr;
		EditorCallbackFn m_Callback;
	};

	class SCARLET_INTERFACE_API EditorInterfaceCheckEvent : public Event
	{
	public:
		EditorInterfaceCheckEvent(InterfaceModule* _Module)
		{
			m_Module = _Module;
		}

		void Bind(bool** _Value)
		{
			m_Value = _Value;
		}

		InterfaceModule* GetModule() { return m_Module; }

		EVENT_CLASS_TYPE(EditorInterfaceCheck)
		EVENT_CLASS_CATEGORY(EventCategoryEditor)

		bool** m_Value;

	private:
		InterfaceModule* m_Module = nullptr;
	};

}