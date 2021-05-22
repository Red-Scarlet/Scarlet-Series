#pragma once

#include <ScarletInterface.h>
#include "EntityTypes.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API Coordinator
	{
	public:
		Coordinator()
		{
			m_ComponentManager = CreateScope<ComponentManager>();
			m_EntityManager = CreateScope<EntityManager>();
			m_SystemManager = CreateScope<SystemManager>();
		}

		~Coordinator()
		{

		}

	public:
		Entity CreateEntity()
		{
			return m_EntityManager->CreateEntity();
		}

		void DestroyEntity(const Entity& entity)
		{
			m_EntityManager->DestroyEntity(entity);
			m_ComponentManager->EntityDestroyed(entity);
			m_SystemManager->EntityDestroyed(entity);
		}

		template<typename T>
		void RegisterComponent()
		{
			m_ComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		T& AddComponent(const Entity& entity, const T& component)
		{
			m_ComponentManager->AddComponent<T>(entity, component);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetComponentType<T>(), true);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->EntitySignatureChanged(entity, signature);

			return m_ComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		void RemoveComponent(const Entity& entity)
		{
			m_ComponentManager->RemoveComponent<T>(entity);

			auto signature = m_EntityManager->GetSignature(entity);
			signature.set(m_ComponentManager->GetComponentType<T>(), false);
			m_EntityManager->SetSignature(entity, signature);

			m_SystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(const Entity& entity)
		{
			return m_ComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		bool HasComponent(const Entity& entity)
		{
			return m_ComponentManager->HasComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType()
		{
			return m_ComponentManager->GetComponentType<T>();
		}

		template<typename T>
		Ref<T> RegisterSystem()
		{
			return m_SystemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(const Signature& signature) 
		{
			m_SystemManager->SetSignature<T>(signature);
		}

	private:
		Scope<ComponentManager> m_ComponentManager;
		Scope<EntityManager> m_EntityManager;
		Scope<SystemManager> m_SystemManager;

	};

}}