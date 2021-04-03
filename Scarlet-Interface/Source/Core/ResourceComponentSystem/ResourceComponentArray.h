#pragma once

#include "Core/Common.h"
#include "ResourceTypes.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	class IResourceComponentArray
	{
	public:
		virtual ~IResourceComponentArray() = default;
		virtual void DestroyResource(const Resource& _Resource) = 0;
	};

	template<typename T>
	class ResourceComponentArray : public IResourceComponentArray
	{
	public:
		void InsertData(const Resource& _Resource, T _Component)
		{
			SCARLET_INTERFACE_ASSERT(m_ResourceToIndexMap.find(_Resource) == m_ResourceToIndexMap.end(), "[RESOURCE] Component added to same entity more than once.");
			
			uint64 newIndex = m_Size;
			m_ResourceToIndexMap[_Resource] = newIndex;
			m_IndexToResourceMap[newIndex] = _Resource;
			m_ComponentArray[newIndex] = _Component;
			m_Size++;
		}

		void RemoveData(const Resource& _Resource)
		{
			SCARLET_INTERFACE_ASSERT(m_ResourceToIndexMap.find(_Resource) != m_ResourceToIndexMap.end(), "[RESOURCE] Removing non-existent component.");

			uint64 indexOfRemovedResource = m_ResourceToIndexMap[_Resource];
			uint64 indexOfLastElement = m_Size - 1;
			m_ComponentArray[indexOfRemovedResource] = m_ComponentArray[indexOfLastElement];

			uint64 resourceOfLastElement = m_IndexToResourceMap[indexOfLastElement];
			m_ResourceToIndexMap[resourceOfLastElement] = indexOfRemovedResource;
			m_IndexToResourceMap[indexOfRemovedResource] = resourceOfLastElement;

			m_ResourceToIndexMap.erase(_Resource);
			m_IndexToResourceMap.erase(indexOfLastElement);
			m_Size--;
		}

		T& GetData(const Resource& _Resource)
		{
			const char* typeName = typeid(T).name();
			
			SCARLET_INTERFACE_ASSERT(m_ResourceToIndexMap.find(_Resource) != m_ResourceToIndexMap.end(), "[RESOURCE] Retrieving non-existent component.");
			return m_ComponentArray[m_ResourceToIndexMap[_Resource]];
		}

		bool HasData(const Resource& _Resource)
		{
			return m_ResourceToIndexMap.find(_Resource) != m_ResourceToIndexMap.end();
		}

		void DestroyResource(const Resource& _Resource) override
		{
			if (m_ResourceToIndexMap.find(_Resource) != m_ResourceToIndexMap.end())
				RemoveData(_Resource);
		}

	private:
		Array<T, MaxResources> m_ComponentArray = {};
		UnorderedMap<Resource, uint64> m_ResourceToIndexMap = {};
		UnorderedMap<uint64, Resource> m_IndexToResourceMap = {};
		Resource m_Size = 0;
	};

}}