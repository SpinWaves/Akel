// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 15/02/2023

#include <Renderer/scene_renderer.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	void SceneRenderer::init(RendererComponent* renderer)
	{
		_pipelines_manager.init(renderer);
	}
}
