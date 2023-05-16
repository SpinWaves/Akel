// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/11/2022
// Updated : 16/05/2023

#include <Scene/scene.h>
#include <Scene/scene_manager.h>
#include <Core/core.h>

namespace Ak
{
	SceneManager::SceneManager(class RendererComponent* renderer)
	: Component("__scenes_manager_component"), _renderer(renderer), _scene_renderer(create_Unique_ptr<SceneRenderer>())
	{}

	void SceneManager::onAttach()
	{
		_timestep = static_cast<float>(SDL_GetTicks64()) / 1000.0f;

		SceneRendererSettings settings;
		_scene_renderer->init(settings);
	}

	void SceneManager::onRender()
	{
		if(!_renderer->isInit())
			return;
		_scene_renderer->render(_scenes[_current_scene_id]);
	}

	void SceneManager::update()
	{
		float timestep = (static_cast<float>(SDL_GetTicks64()) / 1000.0f) - _timestep;
		_timestep = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
		if(!_renderer->isInit())
			onQuit();
		else
			_scenes[_current_scene_id]->onUpdate(timestep);
	}

	void SceneManager::onEvent(Input& input)
	{
		_scenes[_current_scene_id]->onEvent(input);
	}

	void SceneManager::onQuit()
	{
		if(_has_been_destroyed)
			return;

		for(Scene* scene : _scenes)
		{
			scene->onQuit();
			memFree(scene);
		}
		if(_scene_renderer)
			_scene_renderer->destroy();
		_has_been_destroyed = true;
	}
}
