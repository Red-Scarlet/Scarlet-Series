#pragma once

#include "Core/Common.h"
#include "Core/ComponentManager.h"
#include "Core/InterfaceModule.h"

#include "Events/Event.h"
#include "Utilities/Timestep.h"

#include <iostream>

namespace ScarletInterface {

	#define InterfaceSet uint16(0x02)
	#define InterfacePush uint16(0x04)
	#define InterfacePop uint16(0x08)
	#define SignaturePush uint16(0x10)
	#define SignaturePop uint16(0x20)
	#define EventCategoryInterface uint16(0x02)

	class SCARLET_INTERFACE_API InterfaceSetEvent : public Event
	{
	public:
		InterfaceSetEvent() = default;

		EVENT_CLASS_TYPE(InterfaceSet)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)
	};

	class SCARLET_INTERFACE_API InterfacePushEvent : public Event
	{
	public:
		InterfacePushEvent(InterfaceModule* _Module)
			: m_Module(_Module)
		{
		}

		InterfaceModule* GetModule() { return m_Module; }

		EVENT_CLASS_TYPE(InterfacePush)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

	private:
		InterfaceModule* m_Module = nullptr;
	};

	class SCARLET_INTERFACE_API InterfacePopEvent : public Event
	{
	public:
		InterfacePopEvent(InterfaceModule* _Module)
			: m_Module(_Module)
		{
		}

		InterfaceModule* GetModule() { return m_Module; }

		EVENT_CLASS_TYPE(InterfacePop)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

	private:
		InterfaceModule* m_Module = nullptr;
	};

	class SCARLET_INTERFACE_API SignaturePushEvent : public Event
	{
	public:
		SignaturePushEvent(InterfaceModule* _Module)
			: m_Module(_Module)
		{
		}

		InterfaceModule* GetModule() { return m_Module; }

		template<typename T>
		void Bind()
		{
			m_Function = [](const Ref<ComponentManager>& _ComponentManager) {
				if (!_ComponentManager->HasRegisterComponent<T>())
					_ComponentManager->RegisterComponent<T>();
				return _ComponentManager->GetComponentType<T>();
			};
		}

		EVENT_CLASS_TYPE(SignaturePush)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

	private:
		InterfaceModule* m_Module = nullptr;
		Function<InterfaceComponent(const Ref<ComponentManager>& _ComponentManager)> m_Function;
	};

	class SCARLET_INTERFACE_API SignaturePopEvent : public Event
	{
	public:
		SignaturePopEvent(InterfaceModule* _Module)
			: m_Module(_Module)
		{
		}

		InterfaceModule* GetModule() { return m_Module; }

		template<typename T>
		void Bind()
		{
			m_Function = [](const Ref<ComponentManager>& _ComponentManager) {
				if (!_ComponentManager->HasRegisterComponent<T>())
					_ComponentManager->RegisterComponent<T>();
				return _ComponentManager->GetComponentType<T>();
			};
		}

		EVENT_CLASS_TYPE(SignaturePop)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)		
	
	private:
		InterfaceModule* m_Module = nullptr;
		Function<InterfaceComponent(const Ref<ComponentManager>& _ComponentManager)> m_Function;

	};

}