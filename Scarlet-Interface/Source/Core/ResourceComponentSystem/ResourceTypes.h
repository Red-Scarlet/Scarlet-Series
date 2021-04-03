#pragma once

#include "Core/Common.h"

namespace ScarletInterface { namespace ResourceComponentSystem {

	using Resource = uint64;
	const Resource MaxResources = 8192;

	using ResourceComponent = uint8;
	const ResourceComponent MaxResourceComponents = 32;
	using ResourceSignature = Bitset<MaxResourceComponents>;

}}