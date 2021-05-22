#pragma once

#include <ScarletInterface.h>
#include "Backend/Coordinator.h"


namespace SceneGraph {

	using namespace ScarletInterface;

	class Entity;

	class SCARLET_INTERFACE_API Scene : public ParentRef<Scene>
	{
	public:
		friend class SceneSerializer;
		friend class Entity;

	public:
		Scene(const String& _Name);
		virtual ~Scene() = default;

		Entity ReleaseEntity(const Entity& _Entity);
		Entity MakeEntity(const String& _Name);
		Entity CopyEntity(const Entity& _Entity);

		const Ref<Backend::Coordinator>& GetCoordinator();
		const String& GetName();
		void SetName(const String& _Name);

	private:
		String m_Name;
		Vector<Entity*> m_Entities;
		Ref<Backend::Coordinator> m_Coordinator;
		bool m_Closing = false;

	public:
		static Ref<Scene> Create(const String& _Name = "Default");
	};

}