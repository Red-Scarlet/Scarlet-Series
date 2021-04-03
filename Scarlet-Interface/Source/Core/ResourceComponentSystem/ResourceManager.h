#pragma once

#include "Core/Common.h"
#include "ResourceTypes.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	class ResourceManager
	{
	public:
		ResourceManager()
		{
			for (Resource resource = 0; resource < MaxResources; ++resource)
				m_AvailableResources.push(resource);
		}

		Resource CreateResource()
		{
			SCARLET_INTERFACE_ASSERT(m_LivingResourceCount < MaxResources, "[RESOURCE] Too many Resources in existence.");
			Resource resource = m_AvailableResources.front();
			m_AvailableResources.pop();
			m_LivingResourceCount++;
			return resource;
		}

		void DestroyResource(const Resource& _Resource)
		{
			SCARLET_INTERFACE_ASSERT(_Resource < MaxResources, "[RESOURCE] Resource out of range.");
			m_Signatures[_Resource].reset();

			m_AvailableResources.push(_Resource);
			m_LivingResourceCount--;
		}

		void SetSignature(const Resource& _Resource, const ResourceSignature& _Signature)
		{
			SCARLET_INTERFACE_ASSERT(_Resource < MaxResources, "[RESOURCE] Resource out of range.");
			m_Signatures[_Resource] = _Signature;
		}

		ResourceSignature GetSignature(const Resource& _Resource)
		{
			SCARLET_INTERFACE_ASSERT(_Resource < MaxResources, "[RESOURCE] Resource out of range.");
			return m_Signatures[_Resource];
		}

	private:
		Queue<Resource> m_AvailableResources = {};
		Array<ResourceSignature, MaxResources> m_Signatures = {};
		Resource m_LivingResourceCount = {};
	};

}}