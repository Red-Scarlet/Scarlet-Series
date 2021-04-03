#pragma once

#include "Core/Common.h"
#include "ResourceComponentArray.h"
#include "ResourceTypes.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	class ResourceComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();
			SCARLET_INTERFACE_ASSERT(m_ComponentTypes.find(typeName) == m_ComponentTypes.end(), "[RESOURCE] Registering component type more than once.");
			m_ComponentTypes.insert({ typeName, m_NextComponentType });
			m_ComponentArrays.insert({ typeName, CreateRef<ResourceComponentArray<T>>() });
			m_NextComponentType++;
		}

		template<typename T>
		ResourceComponent GetComponentType()
		{
			const char* typeName = typeid(T).name();
			SCARLET_INTERFACE_ASSERT(m_ComponentTypes.find(typeName) != m_ComponentTypes.end(), "[RESOURCE] Component not registered before use");
			return m_ComponentTypes[typeName];
		}

		template<typename T>
		void AddComponent(const Resource& _Resource, T _Component)
		{
			GetComponentArray<T>()->InsertData(_Resource, _Component);
		}

		template<typename T>
		void RemoveComponent(const Resource& _Resource)
		{
			GetComponentArray<T>()->RemoveData(_Resource);
		}

		template<typename T>
		T& GetComponent(const Resource& _Resource)
		{
			return GetComponentArray<T>()->GetData(_Resource);
		}

		template<typename T>
		bool HasComponent(const Resource& _Resource)
		{
			return GetComponentArray<T>()->HasData(_Resource);
		}

		void DestroyResource(const Resource& _Resource)
		{
			for (auto const& pair : m_ComponentArrays) {
				auto const& component = pair.second;
				component->DestroyResource(_Resource);
			}
		}

	private:
		UnorderedMap<const char*, ResourceComponent> m_ComponentTypes = {};
		UnorderedMap<const char*, Ref<IResourceComponentArray>> m_ComponentArrays = {};
		ResourceComponent m_NextComponentType = {};
					
		template<typename T>
		Ref<ResourceComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();
			SCARLET_INTERFACE_ASSERT(m_ComponentTypes.find(typeName) != m_ComponentTypes.end(), "[RESOURCE] Component not registered before use.");
			return std::static_pointer_cast<ResourceComponentArray<T>>(m_ComponentArrays[typeName]);
		}
			
	};

}}