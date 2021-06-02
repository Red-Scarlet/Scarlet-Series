#include "InterfaceSceneGraph.h"

#include <Events/InterfaceEvent.h>
#include "Components/SceneGraphComponent.h"

namespace SceneGraph {

	void InterfaceSceneGraph::OnGlobal(Event& _Event)
	{
		this->SetCallbacks(_Event);

		if (!m_Initialized)
		{
			_Event.Push(new SignaturePushEvent(this))->Bind<SceneGraphComponent>();
			_Event.Push(new ComponentPushEvent(this))->Bind<SceneGraphComponent>(Scene::Create("Default"));
			_Event.Proceed(_Event);

			m_Running = true, m_Initialized = true;
		}

		EventDispatcher dispatcher(_Event);
		dispatcher.Dispatch<AppUpdateEvent>(SCARLET_INTERFACE_BIND_EVENT_FN(InterfaceSceneGraph::OnAppUpdate));
		if (!_Event.Handled) return;
	}

	void InterfaceSceneGraph::OnEditor(Event& _Event)
	{
		if (m_Running)
		{
			if (!m_Panel) m_Panel = PanelUI::Create("SceneGraph Panel");
			if (m_Panel && !m_EditorInitialized)
			{
				m_Panel->Attach(LabelUI::Create("Hello, SceneGraph!"));
				m_EditorInitialized = true;
			}
		
			_Event.Push(new EditorPanelBindEvent())->Bind(m_Panel);
		}
	}

	bool InterfaceSceneGraph::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return m_Running;
	}

}