// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/11/2022
// Updated : 06/01/2023

#include <Scene/scene.h>
#include <Scene/scene_manager.h>

namespace Ak
{
	SceneManager::SceneManager(class RendererComponent* renderer) : Component("__scenes_manager"), _renderer(renderer) {}

	void SceneManager::onRender()
	{
		if(!_renderer->isInit())
			return;

		_scenes[_current_scene_id]->onPreRender();
		
		_scenes[_current_scene_id]->onRender3D();
		_scenes[_current_scene_id]->onRender2D();
	}

	void SceneManager::update()
	{
		if(!_renderer->isInit())
			onQuit();
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
