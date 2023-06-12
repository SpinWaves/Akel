// This file is a part of Akel
// Authors : @kbz_8
// Created : 13/06/2023
// Updated : 13/06/2023

#include <Renderer/RenderPass/render_pass_library.h>

namespace Ak
{
	std::shared_ptr<RenderPass> RenderPassesLibrary::getRenderPass(RenderPassDesc& desc)
	{
		auto it = std::find_if(_cache.begin(), _cache.end(), [&](std::shared_ptr<RenderPass> render_pass) -> bool
		{
			return render_pass->getDescription() == desc;
		});

		if(it != _cache.end())
			return *it;
		std::shared_ptr<RenderPAss> new_render_pass = create_shared_ptr_w<RendrePass>();
		new_render_pass->init(desc);
		_cache.push_back(new_render_pass);
		return new_render_pass;
	}

	void RenderPassesLibrary::clearCache() noexcept
	{
		for(const auto& render_pass : _cache)
			render_pass->destroy();
	}
}
