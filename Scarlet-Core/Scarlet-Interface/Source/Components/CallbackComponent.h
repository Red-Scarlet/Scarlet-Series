#pragma once

#include "Core/Common.h"
#include "Utilities/CallbackTable.h"

namespace ScarletInterface {

	struct SCARLET_INTERFACE_API CallbackComponent
	{
	public:
		Vector<Tuple<std::type_index, Ref<CallbackTable>>> CallbackTables;

		CallbackComponent() = default;
		CallbackComponent(const CallbackComponent&) = default;
	};

}