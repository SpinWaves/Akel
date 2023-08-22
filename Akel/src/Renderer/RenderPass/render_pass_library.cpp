// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/06/2023
// Updated : 22/08/2023

#include <Utils/hash.h>
#include <Renderer/RenderPass/render_pass_library.h>

namespace Ak
{
	std::shared_ptr<RenderPass> RenderPassesLibrary::getRenderPass(RenderPassDesc& desc)
	{
		std::size_t hash = 0;
		hashCombine(hash, desc.clear);
		for(RenderPassAttachement& attachement : desc.attachements)
			hashCombine(hash, *attachement.image, static_cast<int>(attachement.type));
		auto it = _cache.find(hash);
		if(it != _cache.end())
			return it->second;
		std::shared_ptr<RenderPass> new_render_pass = create_shared_ptr_w<RenderPass>();
		new_render_pass->init(desc);
		_cache[hash] = new_render_pass;
		return new_render_pass;
	}

	void RenderPassesLibrary::clearCache() noexcept
	{
		for(const auto& [hash, render_pass] : _cache)
			render_pass->destroy();
		_cache.clear();
	}
}
