// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 14/02/2023

#ifndef __AK_SCENE_RENDERER__
#define __AK_SCENE_RENDERER__

#include <Akpch.h>
#include <Renderer/render_command.h>
#include <Scene/scene.h>
#include <Renderer/Ppipeline/pipelines_manager.h>

namespace Ak
{
	class AK_API SceneRenderer
	{
		public:
			SceneRenderer();

			void render(Scene* scene);

			~SceneRenderer() = default;

		private:
			PipelinesManager _pipelines_manager;
	};
}

#endif
