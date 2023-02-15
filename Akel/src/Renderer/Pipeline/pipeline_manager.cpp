// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 15/02/2023

#include <Renderer/rendererComponent.h>
#include <Renderer/Pipeline/pipeline_manager.h>
#include <Core/memory/sharedPtrWrapper.h>

namespace Ak
{
	void PipelinesManager::init(RendererComponent* renderer)
	{
		_renderer = renderer;
	}

	std:::shared_ptr<GraphicPipeline> PipelinesManager::getPipeline(const PipelineDesc& desc)
	{
		auto it = std::find_if(_cache.begin(), _cache.end(), [&](const GraphicPipeline& pipeline)
		{
			return pipeline.getDescription() == desc;
		});

		if(it != _cache.end())
			return *it;
		std::shared_ptr<GraphicPipeline> new_pipeline = create_shared_ptr<GraphicPipeline>();
		new_pipeline->init(_renderer);
		_cache.push_back(new_pipeline);
		return new_pipeline;
	}

	void PipelinesManager::clearCache() noexcept
	{
		for(const auto& pipeline : _cache)
			pipeline->destroy();
	}
}
