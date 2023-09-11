// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/03/2022
// Updated : 11/09/2023

#include <Utils/plainApplication.h>
#include <Renderer/rendererComponent.h>
#include <Scene/scene_manager.h>

namespace Ak
{
	PlainApplication::PlainApplication(Application& app, const char* name) : _app(app)
	{
		_window = _app.add_component<Ak::WindowComponent>();
		if(name != nullptr)
			_window->title = name;
		_window->fetchSettings();

		_renderer = _app.add_component<RendererComponent>(_window);
		_scene_manager = _app.add_component<Ak::SceneManager>(_renderer);
	}

	void PlainApplication::add_scene(class Scene* scene) noexcept
	{
		_scene_manager->add_scene(scene);
	}
	void PlainApplication::remove_scene(class Scene* scene) noexcept
	{
		_scene_manager->remove_scene(scene);
	}
	void PlainApplication::remove_scene(uint32_t id) noexcept
	{
		_scene_manager->remove_scene(id);
	}
	void PlainApplication::switch_to_scene(uint32_t id) noexcept
	{
		_scene_manager->switch_to_scene(id);
	}
}
