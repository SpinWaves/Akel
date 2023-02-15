// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 15/02/2023

#ifndef __AK_SCENE_RENDERER__
#define __AK_SCENE_RENDERER__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Scene/scene.h>
#include <Renderer/Pipeline/pipelines_manager.h>
#include <Renderer/forward_data.h>

namespace Ak
{
	class AK_API SceneRenderer
	{
		public:
			SceneRenderer();

			void init(class RendererComponent* renderer);
			void render(Scene* scene);

			~SceneRenderer() = default;

			private:
			PipelinesManager _pipelines_manager;
			ForwardData _forward_data;
			std::shared_ptr<Shader> _main_vertex_shader = nullptr;
	};
}

#endif
