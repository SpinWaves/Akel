// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/06/2023
// Updated : 14/06/2023

#ifndef __AK_RENDER_PASS_LIBRARY__
#define __AK_RENDER_PASS_LIBRARY__

#include <Akpch.h>
#include <Utils/selfInstance.h>
#include <Renderer/RenderPass/vk_render_pass.h>

namespace Ak
{
	class AK_API RenderPassesLibrary : public SelfInstance<RenderPassesLibrary>
	{
		public:
			RenderPassesLibrary() = default;
			std::shared_ptr<RenderPass> getRenderPass(RenderPassDesc& desc);
			void clearCache() noexcept;
			~RenderPassesLibrary() = default;

		private:
			std::map<std::size_t, std::shared_ptr<RenderPass>> _cache;
	};
}

#endif
