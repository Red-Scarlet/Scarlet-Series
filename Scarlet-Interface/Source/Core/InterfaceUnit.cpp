#include "InterfaceUnit.h"
#include "IdentifierComponent.h"

namespace ScarletInterface {

	InterfaceUnit::InterfaceUnit(const Ref<ResourceComponentSystem::ResourceCoordinator>& _Coordinator)
		: m_Coordinator(_Coordinator)
	{
		m_Coordinator->RegisterComponent<IdentifierComponent>();
	}

	void InterfaceUnit::OnUpdate()
	{
		if (m_ModuleChange)
		{
			for (auto& m : m_Modules) {
				InterfacePackage& package = m.second;
				if (!package.Created) {
					package.Instance = package.InstantiateScript(m_Coordinator);
					package.Instance->m_Unit = shared_from_this();
					package.Instance->m_Coordinator = m_Coordinator; // DO SIGNS
					package.Instance->m_InterfaceObject = InterfaceObject(m_Coordinator->CreateResource(), m_Coordinator);
					package.Instance->m_InterfaceObject.AddComponent<IdentifierComponent>({ m.first });
					package.Instance->OnCreate(package.Instance->m_InterfaceObject);
					package.Created = true;
					SCARLET_INTERFACE_INFO("Module Created: {0}!", m.first);
				}
			}
			m_ModuleChange = false;
		}

		for (auto& m : m_Modules) {
			InterfacePackage& package = m.second;
			package.Instance->OnUpdate(package.Instance->m_InterfaceObject);
		}
	}

	void InterfaceUnit::OnEvent(Event& _Event)
	{
		for (auto& m : m_Modules) {
			InterfacePackage& package = m.second;
			package.Instance->OnEvent(_Event);
		}
	}

}