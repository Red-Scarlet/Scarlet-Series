#pragma once

#include "Core/Common.h"
#include "ResourceSystem.h"
#include "ResourceTypes.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	class ResourceSystemManager
	{
	public: 
		template<typename T>
		Ref<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();
			SCARLET_INTERFACE_ASSERT(m_System.find(typeName) == m_System.end(), "[RESOURCE] Registering system more than once.");

			auto system = CreateRef<T>();
			m_System.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(const ResourceSignature& _Signature)
		{
			const char* typeName = typeid(T).name();
			m_Signature.insert({ typeName, _Signature });
		}

		void DestroyResource(const Resource& _Resource)
		{
			for (auto pair : m_System) {
				auto system = pair.second;
				system->m_Resources.erase(_Resource);
			}
		}

		void ResourceSignatureChanged(const Resource& _Resource, const ResourceSignature& _ResourceSignature)
		{			
			for (auto& pair : m_System) {
				const char* type = pair.first;
				Ref<ResourceSystem>& system = pair.second;
				ResourceSignature& systemSignature = m_Signature[type];

				if ((_ResourceSignature & systemSignature) == systemSignature)
					system->m_Resources.insert(_Resource);
				else system->m_Resources.erase(_Resource);
			}
		}

	private:
		UnorderedMap<const char*, ResourceSignature> m_Signature = {};
		UnorderedMap<const char*, Ref<ResourceSystem>> m_System = {};

	};

}}