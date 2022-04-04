// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 04/04/2022

#ifndef __AK_VK_IMAGE_VIEW__
#define __AK_VK_IMAGE_VIEW__

#include <Akpch.h>

namespace Ak
{
	class ImageView
	{
		public:
			void init(class SwapChain* swapchain, VkImage& image);
			inline void destroy() noexcept { vkDestroyImageView(Render_Core::get().getDevice()->get(), _image, nullptr); }

            inline VkImageView& operator()() const noexcept { return _image; }
            inline VkImageView& get() const noexcept { return _image; }

		private:
			VkImageView _image;
	};
}

#endif // __AK_VK_IMAGE_VIEW__
