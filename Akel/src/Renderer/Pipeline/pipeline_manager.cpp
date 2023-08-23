// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 23/08/2023

#include <Utils/hash.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Pipeline/pipelines_manager.h>
#include <Core/Memory/sharedPtrWrapper.h>

namespace Ak
{
	std::shared_ptr<GraphicPipeline> PipelinesManager::getPipeline(RendererComponent& renderer, PipelineDesc& desc)
	{
		std::size_t hash = 0;
		hashCombine(hash, desc.depth, desc.culling, desc.mode, desc.topology, desc.line_width);
		hashCombine(hash, desc.swapchain, desc.clear_target);
		for(float bit : desc.clear_color)
			hashCombine(hash, bit);
		for(TextureID id : desc.render_targets)
			hashCombine(hash, id);
		for(ShaderID id : desc.shaders)
			hashCombine(hash, id);
		auto it = _cache.find(hash);
		if(it != _cache.end())
			return it->second;
		std::shared_ptr<GraphicPipeline> new_pipeline = create_shared_ptr_w<GraphicPipeline>();
		new_pipeline->init(&renderer, desc);
		_cache[hash] = new_pipeline;
		return new_pipeline;
	}

	void PipelinesManager::clearCache() noexcept
	{
		ShadersLibrary::get().clearLibrary();
		for(auto [hash, pipeline] : _cache)
			pipeline->destroy();
		_cache.clear();
	}
}
