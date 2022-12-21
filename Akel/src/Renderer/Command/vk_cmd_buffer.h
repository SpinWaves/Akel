// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 21/12/2022

#ifndef __AK_VK_CMD_BUFFER__
#define __AK_VK_CMD_BUFFER__

#include <Akpch.h>

namespace Ak
{
	class CmdBuffer
	{
		public:
			void init(class RendererComponent* renderer);
			void destroy() noexcept;

			void beginRecord(VkCommandBufferUsageFlags usage = 0);
			void endRecord();

			inline VkCommandBuffer& operator()() noexcept { return _cmd_buffer; }
			inline VkCommandBuffer& get() noexcept { return _cmd_buffer; }

		private:
			VkCommandBuffer _cmd_buffer = VK_NULL_HANDLE;
			class RendererComponent* _renderer = nullptr;
			bool _is_recording = false;
	};
}

#endif // __AK_VK_CMD_BUFFER__
