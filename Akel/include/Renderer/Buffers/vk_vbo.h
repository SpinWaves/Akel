// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/04/2022
// Updated : 06/11/2023

#ifndef __AK_VK_VBO__
#define __AK_VK_VBO__

#include "vk_buffer.h"
#include <Renderer/rendererComponent.h>

namespace Ak
{
	class VBO : public Buffer
	{
		public:
			inline void create(uint32_t size, const void* data = nullptr) { Buffer::create(Buffer::kind::dynamic, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, data); }
			void setData(uint32_t size, const void* data);
			inline void bind(RendererComponent& renderer) noexcept { vkCmdBindVertexBuffers(renderer.getActiveCmdBuffer().get(), 0, 1, &_buffer, &_mem_chunck.offset); }
	};

	class C_VBO : public Buffer
	{
		public:
			inline void create(uint32_t size, const void* data) { Buffer::create(Buffer::kind::constant, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, data); }
			inline void bind(RendererComponent& renderer) noexcept { vkCmdBindVertexBuffers(renderer.getActiveCmdBuffer().get(), 0, 1, &_buffer, &_mem_chunck.offset); }
	};
}

#endif // __AK_VK_VBO__
