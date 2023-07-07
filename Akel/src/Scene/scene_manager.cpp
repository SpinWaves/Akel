// This file is a part of Akel
// Authors : @kbz_8
// Created : 23/11/2022
// Updated : 07/07/2023

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
		SceneRendererSettings settings;
		_scene_renderer->init(settings);
	}

	void SceneManager::onRender()
	{
		if(!_renderer->isInit() || _current_scene_id == -1)
			return;
		_scene_renderer->render(_scenes[_current_scene_id]);
	}

	void SceneManager::onUpdate(float delta)
	{
		if(_current_scene_id == -1)
			return;
		if(!_renderer->isInit())
			onQuit();
		else
			_scenes[_current_scene_id]->onUpdate(delta);
	}

	void SceneManager::onEvent(Input& input)
	{
		if(_current_scene_id == -1)
			return;
		_scenes[_current_scene_id]->onEvent(input);
	}

	void SceneManager::onQuit()
	{
		if(_has_been_destroyed)
			return;
		nlohmann::json array = nlohmann::json::array();
		for(Scene* scene : _scenes)
		{
			scene->onQuit();
			nlohmann::json scene_data;
			scene_data["name"] = scene->getName().c_str();
			scene_data["file"] = scene->getFilePath().empty() ? "" : scene->getFilePath();
			array.push_back(scene_data);
			memFree(scene);
		}
		if(!getMainAppProjectFile().keyExists("scenes"))
			getMainAppProjectFile().archive()["scenes"] = array;
		if(_scene_renderer)
			_scene_renderer->destroy();
		_has_been_destroyed = true;
	}
}
