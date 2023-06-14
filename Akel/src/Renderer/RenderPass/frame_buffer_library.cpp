// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/06/2023
// Updated : 14/06/2023

#include <Renderer/RenderPass/frame_buffer_library.h>

namespace Ak
{
	std::shared_ptr<FrameBuffer> FrameBufferLibrary::getFrameBuffer(FrameBufferDesc& desc)
	{
		auto it = std::find_if(_cache.begin(), _cache.end(), [&](std::shared_ptr<FrameBuffer> fb) -> bool
		{
			return fb->getDescription() == desc;
		});

		if(it != _cache.end())
			return *it;
		std::shared_ptr<FrameBuffer> new_fb = create_shared_ptr_w<FrameBuffer>();
		new_fb->init(desc);
		_cache.push_back(new_fb);
		return new_fb;
	}

	void RenderPassesLibrary::clearCache() noexcept
	{
		for(const auto& fb : _cache)
			fb->destroy();
	}
}
