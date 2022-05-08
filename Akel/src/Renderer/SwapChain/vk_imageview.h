// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 08/05/2022

#ifndef __AK_VK_IMAGE_VIEW__
#define __AK_VK_IMAGE_VIEW__

#include <Akpch.h>

namespace Ak
{
	class ImageView
	{
		public:
			void init(class SwapChain* swapchain, VkImage& image);
			void destroy() noexcept;

            inline VkImageView& operator()() noexcept { return _image; }
            inline VkImageView& get() noexcept { return _image; }

		private:
			VkImageView _image = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_IMAGE_VIEW__
