#include "Scarletpch.h"
#include "InterfaceManager.h"

namespace Scarlet {

	InterfaceManager::InterfaceManager() 
	{
		for (Interface i = 0; i < MaxInterface; ++i)
			m_AvailableInterface.push(i);
	}

	Interface InterfaceManager::CreateInterface()
	{
		SCARLET_CORE_ASSERT(m_LivingResourceCount < MaxInterface, "[INTERFACE MANAGER] Too many Interfaces in existence.");

		Interface i = m_AvailableInterface.front();
		m_AvailableInterface.pop();
		m_LivingResourceCount++;

		SCARLET_CORE_INFO("Created Resource: {0}", i);

		return i;
	}

	void InterfaceManager::DestroyInterface(const Interface& _Interface)
	{
		SCARLET_CORE_ASSERT(_Interface < MaxInterface, "[INTERFACE MANAGER] Interface out of range.");

		m_Signatures[_Interface].reset();
		m_AvailableInterface.push(_Interface);
		m_LivingResourceCount--;
	}

	InterfaceSignature InterfaceManager::GetSignature(const Interface& _Interface)
	{
		SCARLET_CORE_ASSERT(_Interface < MaxInterface, "[INTERFACE MANAGER] Interface out of range.");

		return m_Signatures[_Interface];
	}

	void InterfaceManager::SetSignature(const Interface& _Interface, const InterfaceSignature& _Signature)
	{
		SCARLET_CORE_ASSERT(_Interface < MaxInterface, "[INTERFACE MANAGER] Interface out of range.");

		m_Signatures[_Interface] = _Signature;
	}

}