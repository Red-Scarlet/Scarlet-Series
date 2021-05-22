// Copyright 2016-2021 Scarlet-SceneGraph / Red-Scarlet. All rights reserved.
// SceneGraphComponent.h 19/05/2021 - Component Struct.
#pragma once

#include <ScarletInterface.h>
#include "SceneGraph/Scene.h"

namespace SceneGraph {

	using namespace ScarletInterface;

	struct SCARLET_INTERFACE_API SceneGraphComponent
	{
	public:
		Ref<Scene> ActiveScene;

		SceneGraphComponent() = default;
		SceneGraphComponent(const SceneGraphComponent&) = default;
		SceneGraphComponent(const Ref<Scene>& _Scene)
			: ActiveScene(_Scene)
		{
		}
	};

}