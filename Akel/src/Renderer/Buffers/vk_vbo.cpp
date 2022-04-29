// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 29/04/2022

#include "vk_vbo.h"

namespace Ak
{
	void VBO::setData(uint32_t size, const void* data)
	{
		if(size > _mem_chunck.size)
			Core::log::report(ERROR, "Vulkan : trying to store to much data in a vertex buffer (%d on %d)", size, _mem_chunck.size);

		if(data == nullptr)
			Core::log::report(WARNING, "Vulkan : mapping null data in a vertex buffer");

		void* temp = nullptr;
		mapMem(temp);
			std::memcpy(temp, data, static_cast<size_t>(size));
		unmapMem();

		_used_size += size;
	}

	void VBO::setSubData(uint32_t offset, uint32_t size, const void* data)
	{
		if(size + _used_size > _mem_chunck.size)
			Core::log::report(ERROR, "Vulkan : trying to store to much data in a vertex buffer (%d on %d)", size + _used_size, _mem_chunck.size);

		if(data == nullptr)
			Core::log::report(WARNING, "Vulkan : mapping null data in a vertex buffer");

		void* temp = nullptr;
		mapMem(temp, size, offset);
			std::memcpy(temp, data, static_cast<size_t>(size));
		unmapMem();
		
		_used_size += size;
	}
}
