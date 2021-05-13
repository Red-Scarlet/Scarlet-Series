#include "Scarletpch.h"
#include "ModuleManager.h"

namespace Scarlet {

	ModuleManager::ModuleManager()
	{
		m_InterfaceManager = InterfaceManager::Create();
		m_ComponentManager = ComponentManager::Create();
	}

	ModuleManager::~ModuleManager()
	{
		m_InterfaceManager.reset();
		m_ComponentManager.reset();
	}

	void ModuleManager::LoadModule(const String& _FilePath)
	{
		SCARLET_PROFILE_FUNCTION();

		String name = _FilePath.substr(_FilePath.find_last_of("/\\") + 1, _FilePath.length());

		auto iter = m_Modules.find(name.c_str());
		if (iter == m_Modules.end()) {
			InterfaceModule* interfaceModule = InterfaceHandler::Instance().LoadInterface(_FilePath + "\\" + name);
			interfaceModule->m_Interface = m_InterfaceManager->CreateInterface();
			interfaceModule->m_LoadedModule = true;
			m_Modules.insert({ name, interfaceModule });
			SCARLET_CORE_INFO("Module Loaded: {0}", name);
		}
	}

	void ModuleManager::OnEvent(Event& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		if(!_Event.HasCallback()) _Event.SetCallback(SCARLET_BIND_EVENT_FN(ModuleManager::ProcessEvent));

		for (auto pair : m_Modules)
		{
			if (pair.second == nullptr) SCARLET_CORE_ASSERT(SCARLET_ERROR, "Module was Nullptr!");

			if (pair.second->m_LoadedModule)
				InterfaceHandler::Instance().EventInterface(_Event, pair.second);
			else pair.second->OnGlobal(_Event);
		}

		ProcessEvent(_Event);

		if (_Event.Handled) return;
	}

	void ModuleManager::ProcessEvent(Event& _Event)
	{
		while (!_Event.Empty())
		{
			Event* nextEvent = _Event.Back();
			if (nextEvent)
			{
				EventDispatcher dispatcher(*nextEvent);
				dispatcher.Dispatch<InterfaceRequestEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfaceRequest));
				dispatcher.Dispatch<InterfacePushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfacePush));
				dispatcher.Dispatch<InterfacePopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfacePop));
				dispatcher.Dispatch<SignaturePushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnSignaturePush));
				dispatcher.Dispatch<SignaturePopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnSignaturePop));
				dispatcher.Dispatch<ComponentPushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnComponentPush));
				dispatcher.Dispatch<ComponentPopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnComponentPop));
				dispatcher.Dispatch<ComponentComputeEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnComponentCompute));
			}
			_Event.Pop();
		}

		if (_Event.Handled) return;
	}

	bool ModuleManager::OnInterfaceRequest(InterfaceRequestEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		Interface* interface = _Event.GetInterface();
		Interface normal = m_InterfaceManager->CreateInterface();
		*interface = std::move(normal);

		return true;
	}

	bool ModuleManager::OnInterfacePush(InterfacePushEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.m_Data;
		
		if (interfaceModule)
		{
			interfaceModule->m_Name = _Event.m_Name;
			interfaceModule->m_Interface = m_InterfaceManager->CreateInterface();
			m_Modules.insert({ interfaceModule->m_Name, interfaceModule });
			SCARLET_CORE_INFO("Module Loaded: {0}", interfaceModule->m_Name);
		}

		return true;
	}

	bool ModuleManager::OnInterfacePop(InterfacePopEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.GetModule();

		if (interfaceModule) 
		{
			String name = interfaceModule->GetName();
			InterfaceHandler::Instance().UnloadInterface(interfaceModule);
			m_Modules.erase(name);
		}

		return true;
	}

	bool ModuleManager::OnSignaturePush(SignaturePushEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.GetModule();
		if (interfaceModule) 
		{
			// This will check for contained Signature in Signatures, If failed added it, if success update it.
			InterfaceSignature signature;
			signature.set(_Event.m_Function(m_ComponentManager), true);
			auto iter = m_Signatures.find(interfaceModule->GetName());
			if (iter == m_Signatures.end())
				m_Signatures.insert({ interfaceModule->GetName(), signature });
			else iter->second = signature;

			// Loop through every module, 
			for (auto& pair : m_Modules)
			{
				auto const& first = pair.first;
				auto const& second = pair.second;
				auto const& third = m_Signatures[first];

				if ((third & signature) != 0 && second->m_Interface != interfaceModule->m_Interface) 
					interfaceModule->m_Set.insert(second->m_Interface);
			}
		}

		return true;
	}

	bool ModuleManager::OnSignaturePop(SignaturePopEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.GetModule();
		if (interfaceModule) 
		{
			// This will check for contained Signature in Signatures, If failed added it, if success update it.
			
			InterfaceSignature signature;
			signature.set(_Event.m_Function(m_ComponentManager), true);
			//auto iter = m_Signatures.find(interfaceModule->GetName());
			//if (iter == m_Signatures.end())
			//	m_Signatures.insert({ interfaceModule->GetName(), signature });
			//else iter->second = signature;

			// Loop through every module, 
			for (auto& pair : m_Modules)
			{
				auto const& first = pair.first;
				auto const& second = pair.second;
				auto const& third = m_Signatures[first];

				if ((third & signature) != 0 && second->m_Interface != interfaceModule->m_Interface)
					interfaceModule->m_Set.erase(second->m_Interface);
			}
		}

		return true;
	}

	// To Attach Components to interfaces, then update system signatures (So Component will appear in the system)
	bool ModuleManager::OnComponentPush(ComponentPushEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		Interface interface = _Event.GetInterface();

		if (interface == uint64_max) return true;
		InterfaceComponent component = _Event.m_Function(m_ComponentManager, interface, _Event.m_Component);

		// Update The Signatures
		InterfaceSignature signature = m_InterfaceManager->GetSignature(interface);
		signature.set(component, true);
		m_InterfaceManager->SetSignature(interface, signature);

		// Update the system
		InterfaceSignatureChanged(interface, signature);

		SCARLET_CORE_WARN("Pushed Component into {0}: {1}", interface, component);

		return true;
	}

	bool ModuleManager::OnComponentPop(ComponentPopEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		Interface interface = _Event.GetInterface();
		if (interface == uint64_max) return true;
		InterfaceComponent component = _Event.m_Function(m_ComponentManager, interface);

		// Update The Signatures
		InterfaceSignature signature = m_InterfaceManager->GetSignature(interface);
		signature.set(component, false);
		m_InterfaceManager->SetSignature(interface, signature);

		// Update the system
		InterfaceSignatureChanged(interface, signature);

		SCARLET_CORE_WARN("Popped Component into {0}: {1}", interface, component);

		return true;
	}

	bool ModuleManager::OnComponentCompute(ComponentComputeEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		Interface interface = _Event.GetInterface();
		if (interface != uint64_max)
		{
			_Event.m_Data = _Event.m_Function(m_ComponentManager, interface);
			*_Event.m_Component = _Event.m_Data;
		}

		return true;
	}

	void ModuleManager::InterfaceSignatureChanged(const Interface& _Interface, const InterfaceSignature& _InterfaceSignature)
	{
		for (auto const& pair : m_Modules)
		{
			auto const& system = pair.second;
			auto const& type = pair.first;
			auto const& systemSignature = m_Signatures[type];

			if ((_InterfaceSignature & systemSignature) == systemSignature)
			{
				system->m_Set.insert(_Interface);
			}
			else
			{
				system->m_Set.erase(_Interface);
			}
			
		}
	}

}