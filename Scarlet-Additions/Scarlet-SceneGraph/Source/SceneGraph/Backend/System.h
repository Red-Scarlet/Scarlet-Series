#pragma once

#include <ScarletInterface.h>
#include "EntityTypes.h"

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API System
	{
	public:
		Set<Entity> m_Entities;
	};

}}