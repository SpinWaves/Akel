// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 08/12/2022

#include "vk_ubo.h"

namespace Ak
{
	void UBO::create(uint32_t size)
	{
		Buffer::create(Buffer::kind::uniform, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		mapMem(&_map);
		if(_map == nullptr)
			Core::log::report(FATAL_ERROR, "Vulkan : unable to map a uniform buffer");
	}

	void UBO::setData(uint32_t size, const void* data)
	{
		std::memcpy(_map, data, static_cast<size_t>(size));
	}

	void UBO::setDynamicData(uint32_t size, const void* data)
	{
		std::memcpy(_map, data, static_cast<size_t>(size));
		Buffer::flush();
	}
}
