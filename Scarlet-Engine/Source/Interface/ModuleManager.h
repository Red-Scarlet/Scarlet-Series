#pragma once

#include "Core/Common.h"
#include <ScarletInterface.h>
#include <Events/InterfaceEvent.h>

#include "InterfaceHandler.h"
#include "InterfaceManager.h"

namespace Scarlet {

	using namespace ScarletInterface;

	class ModuleManager
	{
	public:
		ModuleManager();
		~ModuleManager();

		void LoadModule(const String& _FilePath);
		void OnEvent(Event& _Event);
		
		void ProcessEvent(Event& _Event);
		bool OnInterfaceRequest(InterfaceRequestEvent& _Event);
		bool OnInterfacePush(InterfacePushEvent& _Event);
		bool OnInterfacePop(InterfacePopEvent& _Event);
		bool OnSignaturePush(SignaturePushEvent& _Event);
		bool OnSignaturePop(SignaturePopEvent& _Event);
		bool OnComponentPush(ComponentPushEvent& _Event);
		bool OnComponentPop(ComponentPopEvent& _Event);
		bool OnComponentCompute(ComponentComputeEvent& _Event);

	private:
		void InterfaceSignatureChanged(const Interface& _Interface, const InterfaceSignature& _InterfaceSignature);

	private:
		UnorderedMap<String, InterfaceModule*> m_Modules = {};	
		UnorderedMap<String, InterfaceSignature> m_Signatures = {};

		Ref<InterfaceManager> m_InterfaceManager;
		Ref<ComponentManager> m_ComponentManager;
	};

}