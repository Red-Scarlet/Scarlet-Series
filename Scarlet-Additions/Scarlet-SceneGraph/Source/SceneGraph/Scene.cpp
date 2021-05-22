#include "Scene.h"
#include "Entity.h"
#include "Components/TagComponent.h"

namespace SceneGraph {

	Scene::Scene(const String& _Name)
		: m_Name(_Name)
	{
	}

	Entity Scene::ReleaseEntity(const Entity& _Entity)
	{
		return Entity({ uint32_max, shared_from_this() });
	}

	Entity Scene::MakeEntity(const String& _Name)
	{
		Entity entity = { m_Coordinator->CreateEntity(), shared_from_this() };
		entity.AddComponent<TagComponent>(_Name);
		m_Entities.push_back(&entity);
		return entity;
	}

	Entity Scene::CopyEntity(const Entity& _Entity)
	{
		return _Entity;
	}

	const Ref<Backend::Coordinator>& Scene::GetCoordinator()
	{
		return m_Coordinator;
	}

	const String& Scene::GetName()
	{
		return m_Name;
	}

	void Scene::SetName(const String& _Name)
	{
		m_Name = _Name;
	}

	Ref<Scene> Scene::Create(const String& _Name)
	{
		return CreateRef<Scene>(_Name);
	}

}