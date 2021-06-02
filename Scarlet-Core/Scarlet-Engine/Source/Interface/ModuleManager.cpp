#include "Scarletpch.h"
#include "ModuleManager.h"

#include "UI/ButtonUI.h"
#include "UI/CheckboxUI.h"
#include "UI/ImageUI.h"
#include "UI/LabelUI.h"
#include "UI/PanelUI.h"
#include "UI/ScrollablePanelUI.h"
#include "UI/SliderUI.h"
#include "UI/TextboxUI.h"

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
			if (!interfaceModule) return;

			interfaceModule->m_Interface = m_InterfaceManager->CreateInterface();
			interfaceModule->m_Info.Name = name;

			bool Ready = true;
			for (String required : interfaceModule->m_Info.Requirements)
				Ready = m_Modules.find(required.c_str()) != m_Modules.end();
			interfaceModule->m_ReadyModule = Ready;

			CallbackComponent callbackComponent;
			{
				callbackComponent.CallbackTables.push_back({ typeid(ButtonUI), ButtonUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(CheckboxUI), CheckboxUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(ImageUI), ImageUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(LabelUI), LabelUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(PanelUI), PanelUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(ScrollablePanelUI), ScrollablePanelUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(SliderUI), SliderUI::s_Callback });
				callbackComponent.CallbackTables.push_back({ typeid(TextboxUI), TextboxUI::s_Callback });
			}

			ComponentPushEvent eventPush(interfaceModule->m_Interface);
			eventPush.Bind<CallbackComponent>(callbackComponent);
			OnComponentPush(eventPush);

			m_Modules.insert({ name, interfaceModule });

			SCARLET_CORE_INFO("Module Loaded: {0}", name);
		}
	}

	void ModuleManager::OnEvent(Event& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		if (!_Event.HasCallback()) { _Event.SetCallback(SCARLET_BIND_EVENT_FN(ModuleManager::ProcessEvent)); }

		for (auto pair : m_Modules)
		{
			if (pair.second == nullptr) SCARLET_CORE_ASSERT(SCARLET_ERROR, "Module was Nullptr!");
			if (pair.second->m_ReadyModule) InterfaceHandler::Instance().EventInterface(_Event, pair.second);
			else pair.second->OnGlobal(_Event);
		}

		if (ProcessEvent(_Event) == false) return;
	}

	bool ModuleManager::ProcessEvent(Event& _Event)
	{
		uint32 HandleCount = _Event.Count();

		while (!_Event.Empty())
		{
			Event* nextEvent = _Event.Back();
			if (nextEvent)
			{
				EventDispatcher dispatcher(*nextEvent);
				HandleCount -= (uint32)dispatcher.Dispatch<InterfaceRequirementEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfaceRequirement));
				HandleCount -= (uint32)dispatcher.Dispatch<InterfaceRequestEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfaceRequest));
				HandleCount -= (uint32)dispatcher.Dispatch<InterfacePushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfacePush));
				HandleCount -= (uint32)dispatcher.Dispatch<InterfacePopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfacePop));
				HandleCount -= (uint32)dispatcher.Dispatch<SignaturePushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnSignaturePush));
				HandleCount -= (uint32)dispatcher.Dispatch<SignaturePopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnSignaturePop));
				HandleCount -= (uint32)dispatcher.Dispatch<ComponentPushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnComponentPush));
				HandleCount -= (uint32)dispatcher.Dispatch<ComponentPopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnComponentPop));
				HandleCount -= (uint32)dispatcher.Dispatch<ComponentComputeEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnComponentCompute));

				HandleCount -= (uint32)dispatcher.Dispatch<EditorHookEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnEditorHook));
				HandleCount -= (uint32)dispatcher.Dispatch<EditorPanelBindEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnEditorPanelBind));
				HandleCount -= (uint32)dispatcher.Dispatch<EditorInterfaceCheckEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnEditorInterfaceCheck));

			}
			_Event.Pop();
		}

		return HandleCount == 0 ? true : false;
	}

	bool ModuleManager::OnInterfaceRequirement(InterfaceRequirementEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		bool ReadyModule = false;
		InterfaceModule* interfaceModule = _Event.GetModule();
		if (interfaceModule)
		{
			uint32 ReadyIndex = 0;
			uint32 RequirementSize = interfaceModule->m_Info.Requirements.size();
			for (String required : interfaceModule->m_Info.Requirements) 
				if (m_Modules.find(required.c_str()) != m_Modules.end()) ReadyIndex++;
			interfaceModule->m_Info.Requirements.clear();
			interfaceModule->m_ReadyModule = ReadyIndex == RequirementSize ? true : false;
			ReadyModule = interfaceModule->m_ReadyModule;
		}

		return ReadyModule;
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
			interfaceModule->m_Info.Name = _Event.m_Name;
			interfaceModule->m_Interface = m_InterfaceManager->CreateInterface();
			m_Modules.insert({ interfaceModule->m_Info.Name, interfaceModule });
			SCARLET_CORE_INFO("Module Loaded: {0}", interfaceModule->m_Info.Name);
		}

		return true;
	}

	bool ModuleManager::OnInterfacePop(InterfacePopEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.GetModule();

		if (interfaceModule) 
		{
			String name = interfaceModule->m_Info.Name;
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
			InterfaceSignature signature;
			signature.set(_Event.m_Function(m_ComponentManager), true);
			auto iter = m_Signatures.find(interfaceModule->m_Info.Name);
			if (iter == m_Signatures.end())
				m_Signatures.insert({ interfaceModule->m_Info.Name, signature });
			else iter->second = signature;

			for (auto& pair : m_Modules)
			{
				if ((m_Signatures[pair.first] & signature) != 0 && pair.second->m_Interface != interfaceModule->m_Interface)
					interfaceModule->m_Set.insert(pair.second->m_Interface);
				else interfaceModule->m_Set.erase(pair.second->m_Interface);
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
			InterfaceSignature signature;
			signature.set(_Event.m_Function(m_ComponentManager), true);

			for (auto& pair : m_Modules)
			{
				if ((m_Signatures[pair.first] & signature) != 0 && pair.second->m_Interface != interfaceModule->m_Interface)
					interfaceModule->m_Set.erase(pair.second->m_Interface);
			}
		}

		return true;
	}

	bool ModuleManager::OnComponentPush(ComponentPushEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		Interface interface = _Event.GetInterface();

		if (interface == uint64_max) return true;
		InterfaceComponent component = _Event.m_Function(m_ComponentManager, interface, _Event.m_Component);

		InterfaceSignature signature = m_InterfaceManager->GetSignature(interface);
		signature.set(component, true);
		m_InterfaceManager->SetSignature(interface, signature);

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

		InterfaceSignature signature = m_InterfaceManager->GetSignature(interface);
		signature.set(component, false);
		m_InterfaceManager->SetSignature(interface, signature);

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

	bool ModuleManager::OnEditorHook(EditorHookEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.GetModule();

		if (interfaceModule)
		{
			m_EditorInterface = interfaceModule;
			m_EditorCallback = _Event.GetCallback();
		}

		return true;
	}

	bool ModuleManager::OnEditorPanelBind(EditorPanelBindEvent& _Event)
	{
		if (m_EditorInterface)
		{
			EditorPanelDrawEvent drawEvent;
			if (!drawEvent.HasCallback()) drawEvent.SetCallback(SCARLET_BIND_EVENT_FN(ModuleManager::ProcessEvent));

			drawEvent.m_UIComponents = std::move(_Event.m_UIComponents);
			m_EditorCallback(drawEvent);
		}

		return true;
	}

	bool ModuleManager::OnEditorInterfaceCheck(EditorInterfaceCheckEvent& _Event)
	{
		SCARLET_PROFILE_FUNCTION();

		InterfaceModule* interfaceModule = _Event.GetModule();
		if (m_EditorInterface) **_Event.m_Value = true;

		return true;
	}

	void ModuleManager::InterfaceSignatureChanged(const Interface& _Interface, const InterfaceSignature& _InterfaceSignature)
	{
		for (auto const& pair : m_Modules)
		{
			if ((_InterfaceSignature & m_Signatures[pair.first]) == m_Signatures[pair.first])
				pair.second->m_Set.insert(_Interface);
			else pair.second->m_Set.erase(_Interface);
		}
	}

}