// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 17/02/2023

#include <Renderer/rendererComponent.h>
#include <Renderer/Pipeline/pipelines_manager.h>
#include <Core/Memory/sharedPtrWrapper.h>

namespace Ak
{
	std::shared_ptr<GraphicPipeline> PipelinesManager::getPipeline(RendererComponent& renderer, PipelineDesc& desc)
	{
		auto it = std::find_if(_cache.begin(), _cache.end(), [&](std::shared_ptr<GraphicPipeline> pipeline) -> bool
		{
			return pipeline->getDescription() == desc;
		});

		if(it != _cache.end())
			return *it;
		std::shared_ptr<GraphicPipeline> new_pipeline = create_shared_ptr_w<GraphicPipeline>();
		new_pipeline->init(&renderer, desc);
		_cache.push_back(new_pipeline);
		return new_pipeline;
	}

	void PipelinesManager::clearCache() noexcept
	{
		ShadersLibrary::get().clearLibrary();
		for(const auto& pipeline : _cache)
			pipeline->destroy();
	}
}
