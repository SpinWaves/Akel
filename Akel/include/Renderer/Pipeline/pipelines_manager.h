// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/02/2023
// Updated : 14/02/2023

#ifndef __AK_PIPELINES_MANAGER__
#define __AK_PIPELINES_MANAGER__

#include <Akpch.h>
#include <Renderer/Pipeline/vk_graphic_pipeline.h>

namespace Ak
{
	class AK_API PipelinesManager
	{
		public:
			std::shared_ptr<GraphicPipeline> getPipeline(const PipelineDesc& desc);

		private:
			inline static std::unordered_map<std::uint32_t, std::shared_ptr<GraphicPipeline>> _cache;
	};
}

#endif
