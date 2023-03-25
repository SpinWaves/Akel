// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2023
// Updated : 25/03/2023

#ifndef __AK_ENTITY_MANAGER__
#define __AK_ENTITY_MANAGER__

#include <Akpch.h>
#include <Scene/entity.h>

namespace Ak
{
	class AK_API EntityManager
	{
		public:
			EntityManager(class Scene* scene);

			Entity create() noexcept;
			Entity create(const std::string& name);

			std::optional<Entity> getEntity(entt::entity entity);

			inline entt::registry& getRegistry() noexcept { return _registry; }

			~EntityManager() = default;

		private:
			entt::registry _registry;
			std::vector<Entity> _entities;
			class Scene* _scene = nullptr;
	};
}

#endif
