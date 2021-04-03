#pragma once

#include "Core/InterfaceUnit.h"
#include "Events/Event.h"

namespace ScarletInterface {

	class InterfaceController
	{
	public:
		InterfaceController()
		{
			Log::Init();

			m_Coordinator = CreateRef<ResourceComponentSystem::ResourceCoordinator>();
			m_Unit = CreateRef<InterfaceUnit>(m_Coordinator);
		}

		~InterfaceController()
		{
			Log::Shutdown();

			m_Unit.reset();
			m_Coordinator.reset();
		}

		void OnUpdate()
		{
			m_Unit->OnUpdate();
		}

		// Should Control Events
		void OnEvent(Event& _Event)
		{
			m_Unit->OnEvent(_Event);
		}

		template<typename T>
		void PushModule()
		{
			m_Unit->PushModule<T>();
		}

		template<typename T>
		void PopModule()
		{
			m_Unit->PopModule<T>();
		}

		template<typename T>
		bool HasModule()
		{
			return m_Unit->HasModule<T>();
		}

	private:
		Ref<InterfaceUnit> m_Unit;
		Ref<ResourceComponentSystem::ResourceCoordinator> m_Coordinator;
	
	};

}