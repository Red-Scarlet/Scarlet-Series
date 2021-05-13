#pragma once

#include "Core/Common.h"
#include <ScarletInterface.h>

namespace Scarlet {

	using namespace ScarletInterface;

	class InterfaceManager
	{
	public:
		InterfaceManager();

		Interface CreateInterface();
		void DestroyInterface(const Interface& _Interface);

		InterfaceSignature GetSignature(const Interface& _Interface);
		void SetSignature(const Interface& _Interface, const InterfaceSignature& _Signature);

	private:
		Queue<Interface> m_AvailableInterface = {};
		Array<InterfaceSignature, MaxInterface> m_Signatures = {};
		uint32 m_LivingResourceCount = {};

	public:
		static Ref<InterfaceManager> Create()
		{ return CreateRef<InterfaceManager>(); }
	};

}