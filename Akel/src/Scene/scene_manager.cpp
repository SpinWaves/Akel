// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/11/2022
// Updated : 23/11/2022

#include <Scene/scene.h>
#include <Scene/scene_manager.h>

void SceneManager::onAttach()
{
	_scenes.clear();
}

void SceneManager::update()
{
	_scenes[_current_scene_id]->update();
}

void SceneManager::onEvent(Input& in)
{
	_scenes[_current_scene_id]->onEvent(in);
}

void SceneManager::onRender()
{
	_scenes[_current_scene_id]->onRender3D();
	_scenes[_current_scene_id]->onRender2D();
}

void SceneManager::onQuit()
{
	for(Scene* scene : _scenes)
		scene->onQuit();
}
