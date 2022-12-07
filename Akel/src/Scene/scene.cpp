// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/12/2022
// Updated : 07/12/2022

#include <Scene/scene.h>
#include <Platform/window.h>
#include <Graphics/matrixes.h>

namespace Ak
{
	Scene::Scene(fString name, WindowComponent* window) : _name(std::move(name)), _window(window)
	{
		if(window == nullptr)
			Core::log::report(FATAL_ERROR, "Scene '%s' : wrong window pointer", name.c_str());
	}

	void Scene::add_2D_entity(Entity2D entity)
	{
		entity.initBuffers();
		_2D_entities.push_back(std::move(entity));
	}

	void Scene::onRender2D()
	{
		Matrixes::ortho(0, 0, _window->size.X, _window->size.Y);

        for(Entity2D& ent : _2D_entities)
		{
			ent._vbo.bind();
			ent._ibo.bind();

			vkCmdDrawIndexed(Render_Core::get().getActiveCmdBuffer().get(), static_cast<uint32_t>(ent._ibo.getSize() / sizeof(uint32_t)), 1, 0, 0, 0);
		}
	}

	void Scene::onRender3D()
	{

	}

	void Scene::onQuit()
	{
		for(auto entity : _2D_entities)
			entity.destroy();
	}
}
