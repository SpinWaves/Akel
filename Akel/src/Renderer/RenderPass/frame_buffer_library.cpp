// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/06/2023
// Updated : 15/06/2023

#include <Renderer/RenderPass/frame_buffer_library.h>

namespace Ak
{
	std::shared_ptr<FrameBuffer> FrameBufferLibrary::getFrameBuffer(FrameBufferDesc& desc)
	{
		if(desc.render_pass.expired())
			Core::log::report(FATAL_ERROR, "Vulkan : unable to get a frame buffer, render pass expired");

		std::size_t hash = 0;
		hashCombine(hash, desc.width, desc.height, desc.layer, /* desc.msaa_level, */desc.mip_index, desc.screen_fbo);
		hashCombine(hash, desc.render_pass.lock());
		for(RenderPassAttachement& attachement : desc.attachements)
			hashCombine(hash, attachement.image, static_cast<int>(attachement.type));
		auto it = _cache.find(hash);
		if(it != _cache.end())
			return it->second;
		std::shared_ptr<FrameBuffer> new_fb = create_shared_ptr_w<FrameBuffer>();
		new_fb->init(desc);
		_cache[hash] = new_fb;
		return new_fb;
	}

	void FrameBufferLibrary::clearCache() noexcept
	{
		for(auto [hash, fb] : _cache)
			fb->destroy();
	}
}
