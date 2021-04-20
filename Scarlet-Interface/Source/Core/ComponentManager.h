#pragma once

#include "Core/Common.h"
#include "Core/ComponentArray.h"
#include "Core/InterfaceTypes.h"

namespace ScarletInterface {

	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();
			m_ComponentTypes.insert({ typeName, m_NextComponentType });
			m_ComponentArrays.insert({ typeName, CreateRef<ComponentArray<T>>() });
			m_NextComponentType++;
		}

		template<typename T>
		bool HasRegisterComponent()
		{
			const char* typeName = typeid(T).name();
			return m_ComponentTypes.find(typeName) != m_ComponentTypes.end();
		}

		template<typename T>
		InterfaceComponent GetComponentType()
		{
			const char* typeName = typeid(T).name();
			return m_ComponentTypes[typeName];
		}

		template<typename T>
		void AddComponent(const Interface& _Interface, T _Component)
		{
			this->GetComponentArray<T>()->InsertData(_Interface, _Component);
		}

		template<typename T>
		void RemoveComponent(const Interface& _Interface)
		{
			this->GetComponentArray<T>()->RemoveData(_Interface);
		}

		template<typename T>
		T& GetComponent(const Interface& _Interface)
		{
			return this->GetComponentArray<T>()->GetData(_Interface);
		}

		template<typename T>
		bool HasComponent(const Interface& _Interface)
		{
			return this->GetComponentArray<T>()->HasData(_Interface);
		}

		void DestroyInterface(const Interface& _Interface)
		{
			for (auto const& pair : m_ComponentArrays) {
				auto const& component = pair.second;
				component->DestroyInterface(_Interface);
			}
		}

	private:
		UnorderedMap<const char*, InterfaceComponent> m_ComponentTypes = {};
		UnorderedMap<const char*, Ref<IComponentArray>> m_ComponentArrays = {};
		InterfaceComponent m_NextComponentType = {};
					
		template<typename T>
		Ref<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();
			return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
		}
			
	};

}