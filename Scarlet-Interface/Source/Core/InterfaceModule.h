#pragma once

#include "Core/Common.h"
#include "ResourceComponentSystem/ResourceSystem.h"	// Move to Core
#include "ResourceComponentSystem/ResourceCoordinator.h" // Move to Core

#include "Core/InterfaceObject.h"
#include "Events/Event.h"

namespace ScarletInterface {

	class InterfaceModule : public ResourceComponentSystem::ResourceSystem
	{
	public:
		friend class InterfaceUnit;

	public:
		virtual ~InterfaceModule() = default;

		virtual void OnCreate(InterfaceObject& _Interface) = 0;
		virtual void OnDestroy(InterfaceObject& _Interface) = 0;
		virtual void OnUpdate(InterfaceObject& _Interface) = 0;
		virtual void OnEvent(Event& _Event) = 0;

		template<typename T>
		void RegisterComponent() 
		{
			m_Coordinator->RegisterComponent<T>();
		}

		template<typename T, typename Component>
		void PushSignature()
		{
			m_Signature.set(m_Coordinator->GetComponentType<Component>());
			m_Coordinator->SetSystemSignature<T>(m_Signature);
		}

		template<typename T, typename Component>
		void PopSignature()
		{
			m_Signature.reset(m_Coordinator->GetComponentType<Component>());
			m_Coordinator->SetSystemSignature<T>(m_Signature);
		}

		template<typename T>
		void PushModule()
		{
			// Can only push child modules.
			m_Unit->PushModule<T>();
		}

		template<typename T>
		void PopModule()
		{
			// Can only pop child modules.
			m_Unit->PopModule<T>();
		}

		template<typename T>
		bool HasModule()
		{
			return m_Unit->HasModule<T>();
		}

		template<typename T>
		Ref<InterfaceModule> GetModule(const char* _Name)
		{
			return m_Unit->GetModule<T>(_Name);
		}

		Vector<InterfaceObject> GetInterfaceObjects()
		{ 
			Vector<InterfaceObject> temp;
			for (ResourceComponentSystem::Resource resource : m_Resources)
				temp.emplace_back(InterfaceObject(resource, m_Coordinator));
			temp.erase(std::remove(temp.begin(), temp.end(), m_InterfaceObject), temp.end());
			return temp;
		};

		InterfaceObject GetInterfaceObject(const uint32& _Index)
		{
			Vector<InterfaceObject> temp;
			temp = GetInterfaceObjects();

			return temp[_Index];
		}

	private:
		Ref<InterfaceUnit> m_Unit;
		Ref<ResourceComponentSystem::ResourceCoordinator> m_Coordinator;
		ResourceComponentSystem::ResourceSignature m_Signature;
		InterfaceObject m_InterfaceObject;
	};

}