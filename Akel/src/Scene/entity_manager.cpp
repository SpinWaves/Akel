// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 25/03/2023

#include <Scene/scene.h>
#include <Scene/entity_manager.h>
#include <Scene/Attributes/name_attribute.h>

namespace Ak
{
	EntityManager::EntityManager(Scene* scene) : _scene(scene) {}

	Entity EntityManager::create() noexcept
	{
		auto e = _registry.create();
		_entities.emplace_back(e, _scene);
		return _entities.back();
	}

	Entity EntityManager::create(const std::string& name)
	{
		auto e = _registry.create();
		_registry.emplace<NameAttribute>(e, name);
		_entities.emplace_back(e, _scene);
		return _entities.back();
	}

	std::optional<Entity> EntityManager::getEntity(entt::entity entity)
	{
		auto it = std::find_if(_entities.begin(), _entities.end(), [&](const Entity& ent)
			{
				return ent.getSubEntity() == entity;
			});
		return it != _entities.end() ? std::optional<Entity>(*it) : std::nullopt;
	}
}
