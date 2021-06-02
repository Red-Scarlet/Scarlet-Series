#pragma once

#include "Core/Common.h"
#include "UI/BaseComponentUI.h"
#include "Utilities/CallbackTable.h"

namespace Scarlet { class ModuleManager; }

namespace ScarletInterface {

	class SCARLET_INTERFACE_API LabelUI : public BaseComponentUI
	{
	public:
		friend class Scarlet::ModuleManager;
		friend class InterfaceModule;

	public:
		LabelUI() = default;
		virtual ~LabelUI() = default;

		virtual void SetName(const String& _Name) = 0;
		virtual const String& GetName() = 0;
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper& _Wrapper);
		static Ref<LabelUI> Create(const String& _Name);
	};

}
