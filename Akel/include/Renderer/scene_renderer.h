// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 08/11/2023

#ifndef __AK_SCENE_RENDERER__
#define __AK_SCENE_RENDERER__

#include <Akpch.h>
#include <Scene/scene.h>
#include <Renderer/Pipeline/pipelines_manager.h>
#include <Graphics/forward_pass.h>

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
			SceneRenderer();

			void init(SceneRendererSettings settings);
			void render(Scene* scene);
			void destroy();

			inline void setRenderTarget(TextureID texture) noexcept { _forward_data.render_texture = texture; }

			~SceneRenderer() = default;

		private:
		//	void skyboxPass(Scene* scene);

		private:
			ForwardPass _forward_pass;
			CommonForwardData _common_forward_data;
			ForwardData _forward_data;
			ForwardSkyboxData _skybox_data;
			Scene* _scene_cache = nullptr;
			SceneRendererSettings _settings;
	};
}

#endif
