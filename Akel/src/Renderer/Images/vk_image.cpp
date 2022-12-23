// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 23/12/2022

#include <Renderer/Images/vk_image.h>
#include <Utils/assert.h>
#include <Core/core.h>

namespace Ak
{
	void Image::create(void* data, uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage)
	{
		if(data == nullptr)
			Core::log::report(WARNING, "Vulkan Image : creating an image with no data in it");
		_buffer.create(Buffer::kind::uniform, width * height * 4, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, data);
	}

	void Image::destroy() noexcept
	{
		Ak_assert(_image != VK_NULL_HANDLE, "trying to destroy an uninit vulkan image");
		vkDestroyImage(Render_Core::get().getDevice().get(), _image, nullptr);
	    vkFreeMemory(Render_Core::get().getDevice().get(), _memory, nullptr);
	}
}
