#pragma once

#include "Core/Common.h"
#include "ResourceComponentSystem/ResourceTypes.h"

namespace ScarletInterface {

	class InterfaceObject
	{
	public:
		InterfaceObject() = default;
		InterfaceObject(const ResourceComponentSystem::Resource& _Resource, const Ref<ResourceComponentSystem::ResourceCoordinator>& _Coordinator)
			: m_Resource(_Resource), m_Coordinator(_Coordinator)
		{
		}

		operator bool() const { return m_Resource != uint32_max; }
		operator ResourceComponentSystem::Resource() const { return m_Resource; }
		bool operator== (const InterfaceObject& other) const { return m_Resource == other.m_Resource; }
		bool operator!= (const InterfaceObject& other) const { return m_Resource != other.m_Resource; }

		template<typename T>
		T& AddComponent(T _Component)
		{
			return m_Coordinator->AddComponent<T>(m_Resource, _Component);
		}
		
		template<typename T>
		void RemoveComponent()
		{
			m_Coordinator->RemoveComponent<T>(m_Resource);
		}
		
		template<typename T>
		T& GetComponent()
		{
			return m_Coordinator->GetComponent<T>(m_Resource);
		}
		
		template<typename T>
		bool HasComponent()
		{
			return m_Coordinator->HasComponent<T>(m_Resource);
		}

	private:
		ResourceComponentSystem::Resource m_Resource;
		Ref<ResourceComponentSystem::ResourceCoordinator> m_Coordinator;
	};

}