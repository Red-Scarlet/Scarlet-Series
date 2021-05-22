#pragma once

#include <ScarletInterface.h>
#include "EntityTypes.h"
#include "ComponentArray.h"

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API ComponentManager
	{
	private:
		template<typename T>
		Ref<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();
			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
		}

	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			m_ComponentTypes.insert({ typeName, m_NextComponentType });
			m_ComponentArrays.insert({ typeName, CreateRef<ComponentArray<T>>() });
			++m_NextComponentType;
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			const char* typeName = typeid(T).name();
			return m_ComponentTypes[typeName];
		}

		template<typename T>
		void AddComponent(const Entity& entity, const T& component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(const Entity& entity)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		T& GetComponent(const Entity& entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		template<typename T>
		bool HasComponent(const Entity& entity)
		{
			return GetComponentArray<T>()->HasData(entity);
		}

		void EntityDestroyed(const Entity& entity)
		{
			for (auto const& pair : m_ComponentArrays) {
				auto const& component = pair.second;
				component->EntityDestroyed(entity);
			}
		}

	private:
		UnorderedMap<const char*, ComponentType> m_ComponentTypes = {};
		UnorderedMap<const char*, Ref<IComponentArray>> m_ComponentArrays = {};
		ComponentType m_NextComponentType = {};		
	};

}}