// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 11/12/2022

#include "vk_ubo.h"

namespace Ak
{
	void UBO::create(uint32_t size)
	{
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			_buffers[i].create(Buffer::kind::uniform, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
			_buffers[i].mapMem(&_maps[i]);
			if(_maps[i] == nullptr)
				Core::log::report(FATAL_ERROR, "Vulkan : unable to map a uniform buffer");
		}
	}

	void UBO::setData(uint32_t size, const void* data)
	{
		std::memcpy(_maps[Render_Core::get().getActiveImageIndex()], data, static_cast<size_t>(size));
	}

	void UBO::setDynamicData(uint32_t size, const void* data)
	{
		std::memcpy(_maps[Render_Core::get().getActiveImageIndex()], data, static_cast<size_t>(size));
		_buffers[Render_Core::get().getActiveImageIndex()].flush();
	}

	unsigned int UBO::getSize() noexcept
	{
		return _buffers[Render_Core::get().getActiveImageIndex()].getSize();
	}
	
	unsigned int UBO::getOffset() noexcept
	{
		return _buffers[Render_Core::get().getActiveImageIndex()].getOffset();
	}
	
	VkDeviceMemory UBO::getDeviceMemory() noexcept
	{
		return _buffers[Render_Core::get().getActiveImageIndex()].getDeviceMemory();
	}
	
	VkBuffer& UBO::operator()() noexcept
	{
		return _buffers[Render_Core::get().getActiveImageIndex()].get();
	}
	
	VkBuffer& UBO::get() noexcept
	{
		return _buffers[Render_Core::get().getActiveImageIndex()].get();
	}

	void UBO::destroy() noexcept
	{
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_buffers[i].destroy();
	}
}
