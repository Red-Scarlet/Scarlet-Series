#include "ResourceCoordinator.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	ResourceCoordinator::ResourceCoordinator()
	{
		m_ResourceManager = CreateScope<ResourceManager>();
		m_ComponentManager = CreateScope<ResourceComponentManager>();
		m_SystemManager = CreateScope<ResourceSystemManager>();
	}

	ResourceCoordinator::~ResourceCoordinator()
	{
		m_ResourceManager.reset();
		m_ComponentManager.reset();
		m_SystemManager.reset();
	}

	Resource ResourceCoordinator::CreateResource()
	{
		m_Resources.push_back(m_ResourceManager->CreateResource());
		return m_Resources.back();
	}

	void ResourceCoordinator::DestroyResource(const Resource& _Resource)
	{
		m_Resources.erase(std::remove(m_Resources.begin(), m_Resources.end(), _Resource), m_Resources.end());

		m_ResourceManager->DestroyResource(_Resource);
		m_ComponentManager->DestroyResource(_Resource);
		m_SystemManager->DestroyResource(_Resource);
	}

}}