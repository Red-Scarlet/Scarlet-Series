#pragma once

#include "Core/Common.h"
#include "ResourceTypes.h"
#include "ResourceManager.h"
#include "ResourceComponentManager.h"
#include "ResourceSystemManager.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	class ResourceCoordinator
	{
	public:
		ResourceCoordinator();
		virtual ~ResourceCoordinator();

	public:
		Resource CreateResource();
		void DestroyResource(const Resource& _Resource);

		template<typename T>
		void RegisterComponent()
		{
			m_ComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		T& AddComponent(const Resource& _Resource, T _Component)
		{
			m_ComponentManager->AddComponent<T>(_Resource, _Component);
			ResourceSignature Signature = m_ResourceManager->GetSignature(_Resource);
			Signature.set(m_ComponentManager->GetComponentType<T>(), true);
			m_ResourceManager->SetSignature(_Resource, Signature);
			m_SystemManager->ResourceSignatureChanged(_Resource, Signature);

			return GetComponent<T>(_Resource);
		}

		template<typename T>
		void RemoveComponent(const Resource& _Resource)
		{
			m_ComponentManager->RemoveComponent<T>(_Resource);

			ResourceSignature Signature = m_ResourceManager->GetSignature(_Resource);
			Signature.set(m_ComponentManager->GetComponentType<T>(), false);
			m_ResourceManager->SetSignature(_Resource, Signature);

			m_SystemManager->ResourceSignatureChanged(_Resource, Signature);
		}

		template<typename T>
		T& GetComponent(const Resource& _Resource)
		{
			return m_ComponentManager->GetComponent<T>(_Resource);
		}

		template<typename T>
		bool HasComponent(const Resource& _Resource)
		{
			return m_ComponentManager->HasComponent<T>(_Resource);
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
		Scope<ResourceManager> m_ResourceManager;
		Scope<ResourceComponentManager> m_ComponentManager;
		Scope<ResourceSystemManager> m_SystemManager;
		Vector<Resource> m_Resources;
	};

}}