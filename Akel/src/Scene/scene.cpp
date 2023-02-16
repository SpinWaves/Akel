// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/12/2022
// Updated : 16/02/2023

#include <Scene/entity_manager.h>
#include <Renderer/Images/texture.h>
#include <Scene/scene.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Buffers/vk_ubo.h>
#include "shader_loader.h"
#include <Scene/entity.h>
#include <Scene/Cameras/base_camera.h>
#include <Graphics/builtin_shaders.h>

namespace Ak
{
	Scene::Scene(fString name) :
		_name(std::move(name)), _entity_manager(create_Unique_ptr<EntityManager>(this)),
		_loader(create_Unique_ptr<ShaderLoader>()), _camera(nullptr)
	{
		_loader->init();
	}

	Entity Scene::createEntity()
	{
		return _entity_manager->create();
	}

	Entity Scene::createEntity(const std::string& name)
	{
		return _entity_manager->create(name);
	}

	entt::registry& Scene::getRegistry() noexcept
	{
		return _entity_manager->getRegistry();
	}

	void Scene::onAttach(RendererComponent* renderer, uint32_t id) noexcept
	{
		_id = id;
		_renderer = renderer;
		if(_forward_shaders.empty())
		{
			_forward_shaders.emplace_back(std::move(_loader->loadShader(shaderlang::nzsl, std::string_view{default_vertex_shader})), renderer);
			_forward_shaders.back().generate();
			_forward_shaders.emplace_back(std::move(_loader->loadShader(shaderlang::nzsl, std::string_view{default_fragment_shader})), renderer);
			_forward_shaders.back().generate();
		}
	}

	void Scene::onUpdate(float timestep)
	{
		Maths::Vec2i win_size = _renderer->getWindow()->size;
		_camera->onUpdate(win_size.X / win_size.Y);
	}

	void Scene::onEvent(Input& input)
	{
		_camera->onEvent(input);
	}

	void Scene::_loadCustomShader(shaderlang lang, std::filesystem::path path)
	{
		_forward_shaders.emplace_back(std::move(_loader->loadShader(lang, std::move(path))), _renderer);
		_forward_shaders.back().generate();
	}

	void Scene::onQuit()
	{
		_loader->destroy();
	}

	Scene::~Scene() {}
}
