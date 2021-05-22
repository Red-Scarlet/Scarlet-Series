#include "InterfaceSceneGraph.h"

#include <Events/InterfaceEvent.h>
#include "Components/SceneGraphComponent.h"

namespace SceneGraph {

	void InterfaceSceneGraph::OnGlobal(Event& _Event)
	{
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

	bool InterfaceSceneGraph::OnAppUpdate(AppUpdateEvent& _Event)
	{
		return true;
	}

}