// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 29/01/2023

#ifndef __AK_VK_CMD_BUFFER__
#define __AK_VK_CMD_BUFFER__

#include <Akpch.h>

namespace Ak
{
	class CmdBuffer
	{
		public:
			void init(class CmdManager* manager);
			void destroy() noexcept;

			void beginRecord(VkCommandBufferUsageFlags usage = 0);
			inline void reset() noexcept { vkResetCommandBuffer(_cmd_buffer, 0); }
			void endRecord();

			inline VkCommandBuffer& operator()() noexcept { return _cmd_buffer; }
			inline VkCommandBuffer& get() noexcept { return _cmd_buffer; }

		private:
			VkCommandBuffer _cmd_buffer = VK_NULL_HANDLE;
			class CmdManager* _manager = nullptr;
			bool _is_recording = false;
	};
}

#endif // __AK_VK_CMD_BUFFER__
