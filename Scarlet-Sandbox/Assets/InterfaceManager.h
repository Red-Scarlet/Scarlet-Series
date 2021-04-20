#pragma once

#include "Core/Common.h"
#include "InterfaceTypes.h"

namespace ScarletInterface {

	class InterfaceManager
	{
	public:
		InterfaceManager()
		{
			for (Interface i = 0; i < MaxInterface; ++i)
				m_AvailableInterface.push(i);
		}

		Interface CreateInterface()
		{
			Interface i = m_AvailableInterface.front();
			m_AvailableInterface.pop();
			m_LivingResourceCount++;
			return i;
		}

		void DestroyInterface(const Interface& _Interface)
		{
			m_Signatures[_Interface].reset();

			m_AvailableInterface.push(_Interface);
			m_LivingResourceCount--;
		}

		void SetSignature(const Interface& _Interface, const ModuleSignature& _Signature)
		{
			m_Signatures[_Interface] = _Signature;
		}

		ModuleSignature GetSignature(const Interface& _Interface)
		{
			return m_Signatures[_Interface];
		}

	private:
		Queue<Interface> m_AvailableInterface = {};
		Array<ModuleSignature, MaxInterface> m_Signatures = {};
		Interface m_LivingResourceCount = {};
	};

}