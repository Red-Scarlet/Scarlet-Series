// Copyright 2016-2021 Scarlet-SceneGraph / Red-Scarlet. All rights reserved.
// RendererContext.h 19/05/2021 - Functional Class.
#pragma once

#include <ScarletInterface.h>
#include <Core/InterfaceEntrypoint.h>

namespace SceneGraph {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API InterfaceSceneGraph : public InterfaceModule
	{
	public:
		virtual void OnGlobal(Event& _Event) override;

	private:
		bool OnAppUpdate(AppUpdateEvent& _Event);

	private:
		bool m_Running = false, m_Initialized = false;
	};

}

INTERFACE_ENTRYPOINT(SceneGraph::InterfaceSceneGraph);