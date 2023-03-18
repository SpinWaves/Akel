// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/12/2022
// Updated : 18/03/2023

#include <Scene/entity_manager.h>
#include <Renderer/Images/texture.h>
#include <Scene/scene.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Buffers/vk_ubo.h>
#include "shader_loader.h"
#include <Scene/entity.h>
#include <Scene/Cameras/base_camera.h>
#include <Graphics/builtin_shaders.h>
#include <Scene/Attributes/model_attribute.h>

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
			std::shared_ptr<Shader> vshader = create_shared_ptr_w<Shader>(_loader->loadShader(shaderlang::nzsl, std::string_view{forward_vertex_shader}), _renderer);
			_forward_shaders.push_back(ShadersLibrary::get().addShaderToLibrary(std::move(vshader)));
			std::shared_ptr<Shader> fshader = create_shared_ptr_w<Shader>(_loader->loadShader(shaderlang::nzsl, std::string_view{forward_fragment_shader}), _renderer);
			_forward_shaders.push_back(ShadersLibrary::get().addShaderToLibrary(std::move(fshader)));
		}
	}

	void Scene::onUpdate(float timestep)
	{
		Maths::Vec2i win_size = _renderer->getWindow()->size;
		_camera->onUpdate(static_cast<float>(win_size.X) / static_cast<float>(win_size.Y));
	}

	void Scene::onEvent(Input& input)
	{
		_camera->onEvent(input);
	}

	void Scene::_loadCustomShader(shaderlang lang, std::filesystem::path path)
	{
		std::shared_ptr<Shader> shader = create_shared_ptr_w<Shader>(_loader->loadShader(lang, std::move(path)), _renderer);
		_forward_shaders.push_back(ShadersLibrary::get().addShaderToLibrary(std::move(shader)));
	}

	void Scene::onQuit()
	{
		auto view = getRegistry().view<ModelAttribute>();
		for(auto e: view)
		{
			ModelAttribute model = view.get<ModelAttribute>(e);
			model.model.destroy();
		}
		_loader->destroy();
	}

	Scene::~Scene() {}
}
