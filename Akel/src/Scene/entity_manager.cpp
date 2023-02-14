// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 14/02/2023

#include <Scene/scene.h>
#include <Scene/entity_manager.h>
#include <Scene/Attributes/name_attribute.h>

namespace Ak
{
	EntityManager::EntityManager(Scene* scene) : _scene(scene) {}

	Entity EntityManager::create() noexcept
	{
		auto e = _registry.create();
		return Entity(e, _scene);
	}

	Entity EntityManager::create(const std::string& name) noexcept
	{
		auto e = _registry.create();
		_registry.emplace<NameAttribute>(e, name);
		return Entity(e, _scene);
	}
}
