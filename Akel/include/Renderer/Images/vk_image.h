// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/12/2022
// Updated : 13/01/2023

#ifndef __AK_VK_IMAGE__
#define __AK_VK_IMAGE__

#include <Akpch.h>

namespace Ak
{
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	class Image
	{
		public:
			Image() = default;

			virtual void create(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImageAspectFlags aspectFlags);
			void destroy() noexcept;

			void copyBuffer(class Buffer& buffer);

			inline VkImage& get() noexcept { return _image; }
			inline VkImage& operator()() noexcept { return _image; }
			inline VkDeviceMemory getDeviceMemory() noexcept { return _memory; }
			inline VkImageView& getImageView() noexcept { return _image_view; }
			inline VkFormat& getFormat() noexcept { return _format; }

			virtual ~Image() = default;

		private:
			VkImage _image = VK_NULL_HANDLE;
			VkDeviceMemory _memory = VK_NULL_HANDLE;
			VkImageView _image_view = VK_NULL_HANDLE;
			uint32_t _width = 0;
			uint32_t _height = 0;
			VkFormat _format;
	};
}

#endif
