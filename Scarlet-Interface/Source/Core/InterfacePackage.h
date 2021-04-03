#pragma once

#include "Core/Common.h"
#include "Core/InterfaceModule.h"

namespace ScarletInterface {
	
	class InterfacePackage
	{
	public:
		Ref<InterfaceModule> Instance = nullptr;
		Ref<InterfaceModule> (*InstantiateScript)(const Ref<ResourceComponentSystem::ResourceCoordinator>&);
		void (*DestroyPackage)(InterfacePackage*);
		bool Created = false;

		template<typename T>
		void Bind()
		{
			InstantiateScript = [](const Ref<ResourceComponentSystem::ResourceCoordinator>& coordinator)
			{ return std::dynamic_pointer_cast<InterfaceModule>(coordinator->RegisterSystem<T>()); };

			DestroyPackage = [](InterfacePackage* nsc) { nsc->Instance.reset(); nsc->Instance = nullptr; };
		}
	};

}