#pragma once

#include "Core/Common.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API BaseComponentUI
	{
	public:
		virtual ~BaseComponentUI() = default;

		virtual void SetName(const String& _Name) = 0;
		virtual const String& GetName() = 0;

		virtual void Draw() = 0;
	};

}