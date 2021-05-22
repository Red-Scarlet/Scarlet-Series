#pragma once

#include <ScarletInterface.h>
#include "Backend/EntityTypes.h"
#include "Scene.h"

namespace SceneGraph {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API Entity
	{
	public:
		Entity() = default;
		Entity(const Backend::Entity& _Entity, const Ref<Scene>& _Scene);
		virtual ~Entity();

		operator bool() const { return m_EntityHandle != uint32_max; }
		operator Backend::Entity() const { return m_EntityHandle; }
		bool operator== (const Entity& other) const { return m_EntityHandle == other.m_EntityHandle; }
		bool operator!= (const Entity& other) const { return m_EntityHandle != other.m_EntityHandle; }

		template<typename T>
		T& AddComponent(T _Component)
		{
			T& component = m_SceneHandle->GetCoordinator()->AddComponent<T>(m_EntityHandle, _Component);
			//m_SceneHandle->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& AddComponent()
		{
			T component = {};
			return AddComponent<T>(component);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_SceneHandle->GetCoordinator()->RemoveComponent<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_SceneHandle->GetCoordinator()->GetComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_SceneHandle->GetCoordinator()->HasComponent<T>(m_EntityHandle);
		}

	public:
		Backend::Entity m_EntityHandle = uint32_max;
		Ref<Scene> m_SceneHandle;
	};

}