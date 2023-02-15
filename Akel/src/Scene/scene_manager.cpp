// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/11/2022
// Updated : 15/02/2023

#include <Scene/scene.h>
#include <Scene/scene_manager.h>
#include <Core/core.h>

namespace Ak
{
	SceneManager::SceneManager(class RendererComponent* renderer)
	: Component("__scenes_manager"), _renderer(renderer), _scene_renderer(create_Unique_ptr<SceneRenderer>())
	{}

	void SceneManager::onAttach()
	{
		getMainAppProjectFile().setBoolValue("__scene_manager", true);
		_timestep = static_cast<float>(SDL_GetTicks64()) / 1000.0f;
	}

	void SceneManager::onRender()
	{
		if(!_renderer->isInit())
			return;
		_scene_renderer->render(_scenes[_current_scene_id]);
	}

	void SceneManager::update()
	{
		_timestep = (static_cast<float>(SDL_GetTicks64()) / 1000.0f) - _timestep;
		if(!_renderer->isInit())
			onQuit();
		else
			_scenes[_current_scene_id]->onUpdate(_timestep);
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
		_has_been_destroyed = true;
	}
}
