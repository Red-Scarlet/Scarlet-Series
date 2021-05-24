#pragma once
#include <ScarletInterface.h>

namespace SceneGraph {

	using namespace ScarletInterface;

	struct TransformComponent
	{
	public:
		Mathematics::Transform Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Mathematics::Transform& _Transform)
			: Transform(_Transform)
		{
		}
	};

}