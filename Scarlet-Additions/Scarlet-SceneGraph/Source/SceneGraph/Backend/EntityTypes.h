#pragma once

#include <ScarletInterface.h>
#include <bitset>

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	using Entity = uint32;
	SCARLET_INTERFACE_API const Entity MAX_ENTITIES = 5000;

	using ComponentType = uint8;
	SCARLET_INTERFACE_API const ComponentType MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;

}}