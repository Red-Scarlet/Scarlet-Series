#pragma once

#include "Core/Common.h"
#include "UI/BasePanelUI.h"
#include "Utilities/CallbackTable.h"

namespace Scarlet { class ModuleManager; }

namespace ScarletInterface {

	class SCARLET_INTERFACE_API ScrollablePanelUI : public BasePanelUI
	{
	public:
		friend class Scarlet::ModuleManager;
		friend class InterfaceModule;

	public:
		ScrollablePanelUI() = default;
		virtual ~ScrollablePanelUI() = default;

		virtual void Attach(const Ref<BaseComponentUI>& _ComponentUI) = 0;
		virtual void Detach(const Ref<BaseComponentUI>& _ComponentUI) = 0;
		virtual void SetName(const String& _Name) = 0;
		virtual const String& GetName() = 0;
		virtual void Draw() = 0;

	private:
		static Ref<CallbackTable> s_Callback;

	public:
		static void PushWrapper(const CallbackWrapper& _Wrapper);
		static Ref<ScrollablePanelUI> Create(const String& _Name);
	};

}