#pragma once

#include "Core/Common.h"
#include <ScarletInterface.h>
#include <Events/InterfaceEvent.h>

#include "InterfaceHandler.h"

namespace Scarlet {

	using namespace ScarletInterface;

	class ModuleManager
	{
	public:
		ModuleManager()
		{
		}

		~ModuleManager()
		{
		}

		void LoadModule(const String& _FilePath)
		{
			SCARLET_PROFILE_FUNCTION();

			// Get The Name. And The Path
			String name = _FilePath.substr(_FilePath.find_last_of("/\\") + 1, _FilePath.length());

			auto iter = m_Modules.find(name.c_str());
			if(iter == m_Modules.end())
				m_Modules.insert({ name.c_str(), InterfaceHandler::Instance().LoadInterface(_FilePath + "\\" + name) });
		}

		void OnEvent(Event& _Event)
		{
			SCARLET_PROFILE_FUNCTION();


			for (auto& pair : m_Modules)
			{
				InterfaceHandler::Instance().EventInterface(_Event, pair.second);
				Event* nextEvent = _Event.GetNext();
				if (nextEvent)
				{
					EventDispatcher dispatcher(*nextEvent);
					dispatcher.Dispatch<SignaturePushEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnSignaturePush));
					dispatcher.Dispatch<SignaturePopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnSignaturePop));
					dispatcher.Dispatch<InterfacePopEvent>(SCARLET_BIND_EVENT_FN(ModuleManager::OnInterfacePop));//
					_Event.ResetEvent();
				}

				// Check if event is all good.

			}


			if (_Event.Handled) return;
		}

		// Signature Change System Array of Component Allowed!
		bool OnSignaturePush(SignaturePushEvent& _Event)
		{
			SCARLET_PROFILE_FUNCTION();

			InterfaceModule* interfaceModule = _Event.GetModule();

			if (interfaceModule) {

			}

			return true;
		}

		bool OnSignaturePop(SignaturePopEvent& _Event)
		{
			SCARLET_PROFILE_FUNCTION();

			InterfaceModule* interfaceModule = _Event.GetModule();

			if (interfaceModule) {

			}

			return true;
		}

		bool OnInterfacePop(InterfacePopEvent& _Event)
		{
			SCARLET_PROFILE_FUNCTION();

			InterfaceModule* interfaceModule = _Event.GetModule();

			if (interfaceModule) {
				String name = interfaceModule->GetName();
				InterfaceHandler::Instance().UnloadInterface(interfaceModule);
				m_Modules.erase(name);
			}
			
			return true;
		}

		void SetSignature(const ModuleSignature& _Signature, const char* _Name)
		{
			// DO EVENT CONDITION;

			//m_Signatures.insert({ _Name, _Signature });
		}

		void DestroyInterface(const Interface& _Interface)
		{
			// DO EVENT CONDITION;

			//for (auto pair : m_Modules) {
			//	auto system = pair.second;
			//	system->.erase(_Interface);
			//}
		}

		void InterfaceSignatureChanged(const Interface& _Interface, const ModuleSignature& _Signature)
		{			
			// DO EVENT CONDITION;

			//for (auto& pair : m_Modules) {
			//	const char* type = pair.first;
			//	InterfaceModule* interfaceModule = pair.second;
			//	ModuleSignature& signature = m_Signatures[type];
			//
			//	if ((_Signature & signature) == signature)
			//		interfaceModule->m_Interfaces.insert(_Interface);
			//	else interfaceModule->m_Interfaces.erase(_Interface);
			//}
		}

	private:
		UnorderedMap<const char*, ModuleSignature> m_Signatures = {};
		UnorderedMap<String, InterfaceModule*> m_Modules = {};

	};

}