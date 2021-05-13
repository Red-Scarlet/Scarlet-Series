#pragma once

#include "Core/Common.h"

namespace ScarletInterface {

	using Interface = uint64;
	const Interface MaxInterface = 8192;

	using InterfaceComponent = uint8;
	const InterfaceComponent MaxInterfaceComponents = 128;

	using InterfaceSignature = Bitset<MaxInterfaceComponents>;

}