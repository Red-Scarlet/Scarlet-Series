#pragma once
#include <ScarletInterface.h>

namespace SceneGraph {
	
	using namespace ScarletInterface;

	struct TagComponent
	{
	public:
		String Name;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const String& _Name)
			: Name(_Name)
		{
		}
	};

}