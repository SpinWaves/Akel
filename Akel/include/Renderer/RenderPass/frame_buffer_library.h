// This file is a part of Akel
// Authors : @kbz_8
// Created : 14/06/2023
// Updated : 16/06/2023

#ifndef __AK_FRAME_BUFFER_LIBRARY__
#define __AK_FRAME_BUFFER_LIBRARY__

#include <Akpch.h>
#include <Utils/selfInstance.h>
#include <Renderer/RenderPass/vk_framebuffer.h>

namespace Ak
{
	class AK_API FrameBufferLibrary : public SelfInstance<FrameBufferLibrary>
	{
		public:
			FrameBufferLibrary() = default;
			std::shared_ptr<FrameBuffer> getFrameBuffer(FrameBufferDesc& desc);
			void clearCache() noexcept;
			~FrameBufferLibrary() = default;

		private:
			std::map<std::size_t, std::shared_ptr<FrameBuffer>> _cache;
	};
}

#endif
