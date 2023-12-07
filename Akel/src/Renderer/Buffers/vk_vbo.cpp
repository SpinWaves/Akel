// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 19/11/2023

#include <Renderer/Buffers/vk_vbo.h>

namespace Ak
{
	void VBO::setData(uint32_t size, const void* data)
	{
		if(size > _size)
			Core::log::report(ERROR, "Vulkan : trying to store to much data in a vertex buffer (%d on %d)", size, _size);

		if(data == nullptr)
			Core::log::report(WARNING, "Vulkan : mapping null data in a vertex buffer");

		void* temp = nullptr;
		mapMem(&temp);
			std::memcpy(temp, data, static_cast<size_t>(size));
		unmapMem();
	}
}
