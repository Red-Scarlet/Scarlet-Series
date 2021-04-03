#pragma once
#include "Core/Common.h"
#include "Core/InterfacePackage.h"
#include "Events/Event.h"

#include <unordered_map>

namespace ScarletInterface {

	class InterfaceUnit : public ParentRef<InterfaceUnit>
	{
	public:
		InterfaceUnit(const Ref<ResourceComponentSystem::ResourceCoordinator>& _Coordinator);
		virtual ~InterfaceUnit() = default;
		void OnUpdate();
		void OnEvent(Event& _Event);

	public:
		template<typename T>
		void PushModule()
		{
			m_ModuleChange = true;

			const char* typeName = typeid(T).name();
			InterfacePackage package = InterfacePackage();
			package.Bind<T>();
			m_Modules[typeName] = package;
		}

		template<typename T>
		void PopModule()
		{
			const char* typeName = typeid(T).name();
			if (m_Modules.find(typeName) != m_Modules.end()) 
				m_Modules.erase(typeName);
		}

		template<typename T>
		bool HasModule()
		{
			const char* typeName = typeid(T).name();
			return m_Modules.find(typeName) != m_Modules.end();
		}

		template<typename T>
		Ref<InterfaceModule> GetModule(const char* _Name)
		{
			auto it = m_Modules.find(_Name);
			if (it != m_Modules.end()) return std::dynamic_pointer_cast<T>(it->second.Instance);
		}

	private:
		std::unordered_map<const char*, InterfacePackage> m_Modules;
		Ref<ResourceComponentSystem::ResourceCoordinator> m_Coordinator;
		bool m_ModuleChange = false;
	};

}