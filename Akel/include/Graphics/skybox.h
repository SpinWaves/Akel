// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/02/2023
// Updated : 08/02/2023

#ifndef __AK_SKYBOX__
#define __AK_SKYBOX__

#include <Akpch.h>
#include <Renderer/Pipeline/vk_graphic_pipeline.h>

namespace Ak
{
	class Skybox
	{
		public:
			Skybox(std::shared_ptr<class CubeMap> map, class RendererComponent* renderer);

			void init(class Scene& scene) noexcept;
			void render() noexcept;
			void destroy() noexcept;

			~Skybox() = default;

		private:
			GraphicPipeline _pipeline;
			std::shared_ptr<class CubeMap> _map;
			class RendererComponent* _renderer = nullptr;
	};
}

#endif
