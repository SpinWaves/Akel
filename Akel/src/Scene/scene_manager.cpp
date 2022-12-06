// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/11/2022
// Updated : 06/12/2022

#include <Scene/scene.h>
#include <Scene/scene_manager.h>

namespace Ak
{
	SceneManager::SceneManager() : Component("__scenes_manager") {}

	void SceneManager::onRender()
	{
		_scenes[_current_scene_id]->onRender3D();
		_scenes[_current_scene_id]->onRender2D();
	}

	void SceneManager::onQuit()
	{
		for(Scene* scene : _scenes)
		{
			scene->onQuit();
			memFree(scene);
		}
	}
}
