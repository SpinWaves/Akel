// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 21/12/2022

#include "vk_ubo.h"
#include <Renderer/rendererComponent.h>

namespace Ak
{
	void UBO::create(RendererComponent* renderer, uint32_t size)
	{
		_renderer = renderer;

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
		std::memcpy(_maps[_renderer->getActiveImageIndex()], data, static_cast<size_t>(size));
	}

	void UBO::setDynamicData(uint32_t size, const void* data)
	{
		std::memcpy(_maps[_renderer->getActiveImageIndex()], data, static_cast<size_t>(size));
		_buffers[_renderer->getActiveImageIndex()].flush();
	}

	unsigned int UBO::getSize() noexcept
	{
		return _buffers[_renderer->getActiveImageIndex()].getSize();
	}
	
	unsigned int UBO::getOffset() noexcept
	{
		return _buffers[_renderer->getActiveImageIndex()].getOffset();
	}
	
	VkDeviceMemory UBO::getDeviceMemory() noexcept
	{
		return _buffers[_renderer->getActiveImageIndex()].getDeviceMemory();
	}
	
	VkBuffer& UBO::operator()() noexcept
	{
		return _buffers[_renderer->getActiveImageIndex()].get();
	}
	
	VkBuffer& UBO::get() noexcept
	{
		return _buffers[_renderer->getActiveImageIndex()].get();
	}

	void UBO::destroy() noexcept
	{
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_buffers[i].destroy();
	}
}
