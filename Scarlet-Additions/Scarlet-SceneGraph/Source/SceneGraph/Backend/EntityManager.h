#pragma once

#include <ScarletInterface.h>
#include "EntityTypes.h"

namespace SceneGraph { namespace Backend {

	using namespace ScarletInterface;

	class SCARLET_INTERFACE_API EntityManager
	{
	public:
		EntityManager()
		{
			for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			{
				m_AvailableEntities.push(entity);
			}
		}

		Entity CreateEntity()
		{
			Entity id = m_AvailableEntities.front();
			m_AvailableEntities.pop();
			++m_LivingEntityCount;
			return id;
		}

		void DestroyEntity(const Entity& entity)
		{
			m_Signatures[entity].reset();

			m_AvailableEntities.push(entity);
			--m_LivingEntityCount;
		}

		void SetSignature(const Entity& entity, const Signature& signature)
		{
			m_Signatures[entity] = signature;
		}

		Signature GetSignature(const Entity& entity)
		{
			return m_Signatures[entity];
		}

	private:
		Queue<Entity> m_AvailableEntities = {};
		Array<Signature, MAX_ENTITIES> m_Signatures = {};
		uint32_t m_LivingEntityCount = {};

	};

}}