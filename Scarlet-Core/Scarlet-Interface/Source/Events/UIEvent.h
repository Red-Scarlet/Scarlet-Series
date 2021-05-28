#pragma once
#include "Core/Common.h"
#include "Core/ComponentManager.h"
#include "Core/InterfaceModule.h"
#include "Events/Event.h"

#include "UI/BaseUI.h"

namespace ScarletInterface {

	#define EditorDraw uint16(0x0000)
	#define EventCategoryEditor uint16(0x02)

	class SCARLET_INTERFACE_API EditorDrawEvent : public Event
	{
	public:
		EditorDrawEvent()
		{
		}

		void Push(const Ref<BaseUI>& _UI)
		{
			m_UIComponents.push_back(_UI);
		}

		void Draw()
		{
			for (Ref<BaseUI> ui : m_UIComponents)
				ui->Draw();
		}

		EVENT_CLASS_TYPE(EditorDraw)
		EVENT_CLASS_CATEGORY(EventCategoryEditor)

	private:
		Vector<Ref<BaseUI>> m_UIComponents;
	};

}