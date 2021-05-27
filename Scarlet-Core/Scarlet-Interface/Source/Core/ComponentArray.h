#pragma once

#include "Core/Common.h"
#include "InterfaceTypes.h"

namespace ScarletInterface {

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void DestroyInterface(const Interface& _Interface) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(const Interface& _Interface, T _Component)
		{
			uint64 index = m_Size;
			m_InterfaceToIndexMap[_Interface] = index;
			m_IndexToInterfaceMap[index] = _Interface;
			m_ComponentArray[index] = _Component;
			m_Size++;
		}

		void RemoveData(const Interface& _Interface)
		{
			uint64 indexOfRemovedResource = m_InterfaceToIndexMap[_Interface];
			uint64 indexOfLastElement = m_Size - 1;
			m_ComponentArray[indexOfRemovedResource] = m_ComponentArray[indexOfLastElement];

			uint64 resourceOfLastElement = m_IndexToInterfaceMap[indexOfLastElement];
			m_InterfaceToIndexMap[resourceOfLastElement] = indexOfRemovedResource;
			m_IndexToInterfaceMap[indexOfRemovedResource] = resourceOfLastElement;

			m_InterfaceToIndexMap.erase(_Interface);
			m_IndexToInterfaceMap.erase(indexOfLastElement);
			m_Size--;
		}

		T& GetData(const Interface& _Interface)
		{
			const char* typeName = typeid(T).name();	
			return m_ComponentArray[m_InterfaceToIndexMap[_Interface]];
		}

		bool HasData(const Interface& _Interface)
		{
			return m_InterfaceToIndexMap.find(_Interface) != m_InterfaceToIndexMap.end();
		}

		void DestroyInterface(const Interface& _Interface) override
		{
			if (m_InterfaceToIndexMap.find(_Interface) != m_InterfaceToIndexMap.end())
				RemoveData(_Interface);
		}

	private:
		Array<T, MaxInterface> m_ComponentArray = {};
		UnorderedMap<Interface, uint64> m_InterfaceToIndexMap = {};
		UnorderedMap<uint64, Interface> m_IndexToInterfaceMap = {};
		Interface m_Size = 0;
	};

}