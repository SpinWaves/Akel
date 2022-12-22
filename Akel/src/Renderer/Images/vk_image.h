// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/12/2022
// Updated : 22/12/2022

#ifndef __AK_VK_IMAGE__
#define __AK_VK_IMAGE__

#include <Akpch.h>
#include <Renderer/Buffers/vk_buffer.h>

namespace Ak
{
	class Image
	{
		public:
			Image() = default;

			void create(void* data, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage);
			void destroy() noexcept;

			inline VkImage& get() noexcept { return _image; }
			inline VkImage& operator() noexcept { return _image; }
			inline VkDeviceMemory getDeviceMemory() noexcept { return _memory; }

			virtual ~Image() = default;

		private:
			Buffer _buffer;
			VkImage _image = VK_NULL_HANDLE;
			VkDeviceMemory _memory = VK_NULL_HANDLE;
	};
}

#endif
