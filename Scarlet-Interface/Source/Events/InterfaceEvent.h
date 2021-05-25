#pragma once

#include "Core/Common.h"
#include "Core/ComponentManager.h"
#include "Core/InterfaceModule.h"

#include "Events/Event.h"
#include "Utilities/Timestep.h"

#include <iostream>

namespace ScarletInterface {

	#define InterfaceRequirements uint16(0x0002)
	#define InterfaceRequest uint16(0x0004)
	#define InterfacePush uint16(0x0008)
	#define InterfacePop uint16(0x0010)
	#define SignaturePush uint16(0x0020)
	#define SignaturePop uint16(0x0040)
	#define ComponentPush uint16(0x0080)
	#define ComponentPop uint16(0x0100)
	#define ComponentCompute uint16(0x0200)

	#define EventCategoryInterface uint16(0x01)

	class SCARLET_INTERFACE_API InterfaceRequirementEvent : public Event
	{
	public:
		InterfaceRequirementEvent(InterfaceModule* _Module)
		{

			m_Module = _Module;
		}

		InterfaceModule* GetModule() { return m_Module; }

		void Set(const Vector<String>& _Requirement)
		{
			m_Module->m_Info.Requirements = _Requirement;
		}

		EVENT_CLASS_TYPE(InterfaceRequirements)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

	private:
		InterfaceModule* m_Module = nullptr;
	};

	class SCARLET_INTERFACE_API InterfaceRequestEvent : public Event
	{
	public:
		InterfaceRequestEvent(Interface* _Interface)
		{
			m_Interface = _Interface;
		}

		Interface* GetInterface() { return m_Interface; }

		EVENT_CLASS_TYPE(InterfaceRequest)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

	private:
		Interface* m_Interface = nullptr;
	};

	class SCARLET_INTERFACE_API InterfacePushEvent : public Event
	{
	public:
		InterfacePushEvent(InterfaceModule* _Module)
		{
			m_Module = _Module;
		}

		InterfaceModule* GetModule() { return m_Module; }

		template<typename T>
		void Bind(T* _Interface)
		{
			const char* typeName = typeid(T).name();

			m_Name = String(typeName);
			m_Data = (InterfaceModule*)_Interface;
		}

		EVENT_CLASS_TYPE(InterfacePush)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

		String m_Name;
		InterfaceModule* m_Data;

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

		Function<InterfaceComponent(const Ref<ComponentManager>& _ComponentManager)> m_Function;

	private:
		InterfaceModule* m_Module = nullptr;
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
	
		Function<InterfaceComponent(const Ref<ComponentManager>& _ComponentManager)> m_Function;

	private:
		InterfaceModule* m_Module = nullptr;

	};

	class SCARLET_INTERFACE_API ComponentPushEvent : public Event
	{
	public:
		ComponentPushEvent(InterfaceModule* _Module)
		{
			m_Interface = _Module->m_Interface;
		}

		ComponentPushEvent(const Interface& _Interface)
		{
			m_Interface = _Interface;
		}

		const Interface& GetInterface() { return m_Interface; }

		template<typename T>
		void Bind(T _Component)
		{
			m_Function = [](const Ref<ComponentManager>& _ComponentManager, const Interface& _Interface, AnyData _Component) {
				if (!_ComponentManager->HasRegisterComponent<T>())
					_ComponentManager->RegisterComponent<T>();
				if (!_ComponentManager->HasComponent<T>(_Interface))
					_ComponentManager->AddComponent<T>(_Interface, AnyCast<T>(_Component));

				return _ComponentManager->GetComponentType<T>();
			};

			m_Component = _Component;
		}

		EVENT_CLASS_TYPE(ComponentPush)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

		Function<InterfaceComponent(const Ref<ComponentManager>& _ComponentManager, const Interface& _Interface, AnyData _Component)> m_Function;
		AnyData m_Component;

	private:
		Interface m_Interface = uint64_max;
	};

	class SCARLET_INTERFACE_API ComponentPopEvent : public Event
	{
	public:
		ComponentPopEvent(InterfaceModule* _Module)
		{
			m_Interface = _Module->m_Interface;
		}

		ComponentPopEvent(const Interface& _Interface)
		{
			m_Interface = _Interface;
		}

		const Interface& GetInterface() { return m_Interface; }

		template<typename T>
		void Bind()
		{
			m_Function = [](const Ref<ComponentManager>& _ComponentManager, const Interface& _Interface) {
				if (!_ComponentManager->HasRegisterComponent<T>())
					_ComponentManager->RegisterComponent<T>();
				if (_ComponentManager->HasComponent<T>(_Interface))
					_ComponentManager->RemoveComponent<T>(_Interface);
				return _ComponentManager->GetComponentType<T>();
			};
		}

		EVENT_CLASS_TYPE(ComponentPop)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

		Function<InterfaceComponent(const Ref<ComponentManager>& _ComponentManager, const Interface& _Interface)> m_Function;

	private:
		Interface m_Interface = uint64_max;
	};

	class SCARLET_INTERFACE_API ComponentComputeEvent : public Event
	{
	public:
		using EventCallbackFn = std::function<void()>;

		ComponentComputeEvent(InterfaceModule* _Module)
		{
			m_Interface = _Module->m_Interface;
		}

		ComponentComputeEvent(const Interface& _Interface)
			: m_Interface(_Interface)
		{
		}

		const Interface& GetInterface() { return m_Interface; }

		template<typename T>
		void Retrieve(T** _Component)
		{
			m_Function = [](const Ref<ComponentManager>& _ComponentManager, const Interface& _Interface) {
				if (!_ComponentManager->HasRegisterComponent<T>())
					_ComponentManager->RegisterComponent<T>();
				if (_ComponentManager->HasComponent<T>(_Interface)) return (void*)(T*)&_ComponentManager->GetComponent<T>(_Interface);
			};

			m_Component = (void**)_Component;
			*m_Component = &(*(T*)m_Data);
		}

		EVENT_CLASS_TYPE(ComponentCompute)
		EVENT_CLASS_CATEGORY(EventCategoryInterface)

		Function<void*(const Ref<ComponentManager>& _ComponentManager, const Interface& _Interface)> m_Function;
		void** m_Component;
		void* m_Data;

	private:
		Interface m_Interface = uint64_max;

	};

}