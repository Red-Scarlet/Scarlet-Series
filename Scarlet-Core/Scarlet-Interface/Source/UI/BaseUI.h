#pragma once

#include "Core/Common.h"

namespace ScarletInterface {

	class SCARLET_INTERFACE_API BaseUI
	{
	public:
		friend class EditorDrawEvent;

	public:
		virtual ~BaseUI() = default;

	private:
		virtual void Draw() = 0;
	};

}