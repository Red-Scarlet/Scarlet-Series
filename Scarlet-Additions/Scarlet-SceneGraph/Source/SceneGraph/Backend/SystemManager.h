#pragma once

#include <ScarletInterface.h>
#include "EntityTypes.h"
#include "System.h"

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API SystemManager
	{
	public: 
		template<typename T>
		Ref<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			auto system = CreateRef<T>();
			m_System.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(const Signature& signature)
		{
			const char* typeName = typeid(T).name();
			m_Signature.insert({ typeName, signature });
		}

		void EntityDestroyed(const Entity& entity)
		{
			for (auto const& pair : m_System) {
				auto const& system = pair.second;
				system->m_Entities.erase(entity);
			}
		}

		void EntitySignatureChanged(const Entity& entity, const Signature& entitySignature)
		{
			for (auto const& pair : m_System)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_Signature[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_Entities.insert(entity);
				}
				else
				{
					system->m_Entities.erase(entity);
				}
			}
		}

	private:
		UnorderedMap<const char*, Signature> m_Signature = {};
		UnorderedMap<const char*, Ref<System>> m_System = {};

	};

}}