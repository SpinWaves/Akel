// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 16/02/2023

#ifndef __AK_PIPELINES_MANAGER__
#define __AK_PIPELINES_MANAGER__

#include <Akpch.h>
#include <Renderer/Pipeline/vk_graphic_pipeline.h>

namespace Ak
{
	class AK_API PipelinesManager
	{
		public:
			PipelinesManager() = default;

			std::shared_ptr<GraphicPipeline> getPipeline(class RendererComponent& renderer, PipelineDesc& desc);
			void clearCache() noexcept;

			~PipelinesManager() = default;

		private:
			std::vector<std::shared_ptr<GraphicPipeline>> _cache;
	};
}

#endif
