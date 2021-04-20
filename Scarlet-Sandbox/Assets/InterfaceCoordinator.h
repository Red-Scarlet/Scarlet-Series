#pragma once

#include "Core/Common.h"
#include "Core/InterfaceTypes.h"
#include "Core/InterfaceManager.h"
#include "Core/ComponentManager.h"
#include "Core/ModuleManager.h"

namespace ScarletInterface {

	class ResourceCoordinator
	{
	public:
		ResourceCoordinator();
		virtual ~ResourceCoordinator();

	public:
		Interface CreateInterface();
		void DestoryInterface(const Interface& _Interface);

		template<typename T>
		void RegisterComponent()
		{
			m_ComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		bool HasRegisterComponent()
		{
			return m_ComponentManager->HasRegisterComponent<T>();
		}

		template<typename T>
		T& AddComponent(const Interface& _Interface, T _Component)
		{
			m_ComponentManager->AddComponent<T>(_Interface, _Component);
			ResourceSignature Signature = m_ResourceManager->GetSignature(_Interface);
			Signature.set(m_ComponentManager->GetComponentType<T>(), true);
			m_ResourceManager->SetSignature(_Interface, Signature);
			m_SystemManager->ResourceSignatureChanged(_Interface, Signature);

			return GetComponent<T>(_Resource);
		}

		template<typename T>
		void RemoveComponent(const Interface& _Interface)
		{
			m_ComponentManager->RemoveComponent<T>(_Interface);

			ResourceSignature Signature = m_ResourceManager->GetSignature(_Interface);
			Signature.set(m_ComponentManager->GetComponentType<T>(), false);
			m_ResourceManager->SetSignature(_Interface, Signature);

			m_SystemManager->ResourceSignatureChanged(_Interface, Signature);
		}

		template<typename T>
		T& GetComponent(const Resource& _Interface)
		{
			return m_ComponentManager->GetComponent<T>(_Interface);
		}

		template<typename T>
		bool HasComponent(const Resource& _Interface)
		{
			return m_ComponentManager->HasComponent<T>(_Interface);
		}

		template<typename T>
		ResourceComponent GetComponentType()
		{
			return m_ComponentManager->GetComponentType<T>();
		}

		template<typename T>
		Ref<T> RegisterSystem()
		{
			return m_SystemManager->RegisterSystem<T>();
		}

		void RegisterSystem(const Ref<ResourceSystem>& _System, const char* _Name)
		{
			m_SystemManager->RegisterSystem(_System, _Name);
		}

		template<typename T>
		void SetSystemSignature(const ResourceSignature& _Signature)
		{
			m_SystemManager->SetSignature<T>(_Signature);

			for (const Resource& resource : m_Resources) {			
				ResourceSignature Signature = m_ResourceManager->GetSignature(resource);
				if(Signature == _Signature) m_SystemManager->ResourceSignatureChanged(resource, _Signature);
			}
		}

	private:
		Ref<ResourceManager> m_ResourceManager;
		Ref<ResourceComponentManager> m_ComponentManager;
		Ref<ResourceSystemManager> m_SystemManager;
		Vector<Interface> m_Interface;
	};

}