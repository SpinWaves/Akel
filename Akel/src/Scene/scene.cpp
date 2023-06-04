// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/12/2022
// Updated : 04/06/2023

#include <Scene/entity_manager.h>
#include <Renderer/Images/texture.h>
#include <Scene/scene.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Buffers/vk_ubo.h>
#include "shader_loader.h"
#include <Scene/entity.h>
#include <Scene/Cameras/base_camera.h>
#include <Graphics/builtin_shaders.h>
#include <Scene/Attributes/attributes.h>
#include <Core/file_loader.h>
#include <Platform/resourceManager.h>
#include <Scene/scene_serializer.h>

namespace Ak
{
	Scene::Scene(fString name) :
		_name(std::move(name)), _entity_manager(create_Unique_ptr<EntityManager>(this)),
		_loader(create_Unique_ptr<ShaderLoader>()), _camera(nullptr)
	{
		_loader->init();
		if(getMainAppProjectFile().archive()["use_default_resource_system"] == true)
		{
			std::string filename = _name.c_str();
			filename.append(".akscn");
			_filepath = Res::get().getScenesPath() / filename;
		}
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

		auto script_view = getRegistry().view<ScriptAttribute>();
		for(auto e: script_view)
		{
			ScriptAttribute& script = script_view.get<ScriptAttribute>(e);
			std::optional<Entity> entity = _entity_manager->getEntity(e);
			if(_first_update)
				script.onInit(&(*entity));
			script.onUpdate(&(*entity), timestep);
		}

		auto audio_view = getRegistry().group<AudioAttribute>(entt::get<TransformAttribute>);
		for(auto e : audio_view)
		{
			AudioAttribute& audio = audio_view.get<AudioAttribute>(e);
			const TransformAttribute& trans = audio_view.get<TransformAttribute>(e);

			audio.sound.setPosition(trans.position);
		}

		_first_update = false;
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
		auto script_view = getRegistry().view<ScriptAttribute>();
		for(auto e: script_view)
		{
			ScriptAttribute& script = script_view.get<ScriptAttribute>(e);
			std::optional<Entity> entity = _entity_manager->getEntity(e);
			script.onQuit(&(*entity));
			memFree(script._script);
		}

		auto audio_view = getRegistry().view<AudioAttribute>();
		for(auto e: audio_view)
		{
			AudioAttribute& audio = audio_view.get<AudioAttribute>(e);
			audio.sound.destroy();
		}

		auto model_view = getRegistry().view<ModelAttribute>();
		for(auto e: model_view)
		{
			ModelAttribute& model = model_view.get<ModelAttribute>(e);
			model.model.destroy();
		}

		_loader->destroy();

		if(getMainAppProjectFile().archive()["use_default_resource_system"] == true)
		{
			std::string filename = _name.c_str();
			filename.append(".akscn");
			SceneSerializer serializer(this);
			serializer.serialize(Res::get().getScenesPath() / filename);
		}
	}

	Scene::~Scene() {}
}
