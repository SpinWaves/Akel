// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 16/02/2023

#ifndef __AK_SCENE_RENDERER__
#define __AK_SCENE_RENDERER__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Scene/scene.h>
#include <Renderer/Pipeline/pipelines_manager.h>
#include <Renderer/forward_data.h>

namespace Ak
{
	struct SceneRendererSettings
	{
		bool shadows = true;
		bool geometries = true;
		bool skybox = true;
		bool post_process = false;
	};

	class SceneRenderer
	{
		public:
			SceneRenderer() = default;

			void init(SceneRendererSettings settings);
			void render(Scene* scene);
			void destroy();

			~SceneRenderer() = default;

		private:
			void forwardPass(Scene* scene);

			PipelinesManager _pipelines_manager;
			ForwardData _forward_data;
			Scene* _scene_cache = nullptr;
			SceneRendererSettings _settings;
	};
}

#endif
