// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/03/2022
// Updated : 29/03/2022

#ifndef __AK_VK_RENDER_PASS__
#define __AK_VK_RENDER_PASS__

#include <Akpch.h>
#include <Utils/nonCopyable.h>

namespace Ak
{
	class Renderpass
	{
		public:

			operator const VkRenderPass& () const { return _renderpass; }
			inline const VkRenderPass& getRenderpass() const noexcept { return _renderpass; }

		private:
			VkRenderPass _renderpass = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_RENDER_PASS__
