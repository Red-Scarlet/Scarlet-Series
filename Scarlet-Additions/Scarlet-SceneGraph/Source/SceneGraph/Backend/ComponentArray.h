#pragma once

#include <ScarletInterface.h>
#include "EntityTypes.h"

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(const Entity& entity) = 0;
	};

	template<typename T>
	class SCARLET_INTERFACE_API ComponentArray : public IComponentArray
	{
	public:
		void InsertData(const Entity& entity, const T& component)
		{
			uint32 newIndex = m_Size;
			m_EntityToIndexMap[entity] = newIndex;
			m_IndexToEntityMap[newIndex] = entity;
			m_ComponentArray[newIndex] = component;
			++m_Size;
		}

		void RemoveData(const Entity& entity)
		{
			uint32 indexOfRemovedEntity = m_EntityToIndexMap[entity];
			uint32 indexOfLastElement = m_Size - 1;
			m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

			Entity entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
			m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_EntityToIndexMap.erase(entity);
			m_IndexToEntityMap.erase(indexOfLastElement);

			--m_Size;
		}

		T& GetData(const Entity& entity)
		{
			return m_ComponentArray[m_EntityToIndexMap[entity]];
		}

		bool HasData(const Entity& entity)
		{
			return m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end();
		}

		void EntityDestroyed(const Entity& entity) override
		{
			if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}

	private:
		Array<T, MAX_ENTITIES> m_ComponentArray = {};
		UnorderedMap<Entity, uint32> m_EntityToIndexMap = {};
		UnorderedMap<uint32, Entity> m_IndexToEntityMap = {};
		uint32 m_Size;
	};

}}