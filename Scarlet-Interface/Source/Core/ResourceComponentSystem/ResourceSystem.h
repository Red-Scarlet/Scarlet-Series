#pragma once

#include "Core/Common.h"
#include "ResourceTypes.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	class ResourceSystem
	{
	public:
		friend class ResourceSystemManager;

	protected:
		Set<Resource> m_Resources;
	};

}}