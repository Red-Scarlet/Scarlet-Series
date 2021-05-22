#include "Entity.h"

namespace SceneGraph {

	Entity::Entity(const Backend::Entity& _Entity, const Ref<Scene>& _Scene)
		: m_EntityHandle(_Entity), m_SceneHandle(_Scene)
	{
	}

	Entity::~Entity()
	{
	}

}