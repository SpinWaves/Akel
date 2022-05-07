// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 07/05/2022

#ifndef __AK_VK_CMD_BUFFER__
#define __AK_VK_CMD_BUFFER__

#include <Akpch.h>
#include <Renderer/Core/render_core.h>

namespace Ak
{
	class CmdBuffer
	{
		public:
			void init();
			void destroy();

			void beginRecord(VkCommandBufferUsageFlags usage = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
			void endRecord();

			inline VkCommandBuffer& operator()() noexcept { return _cmd_buffer; }
			inline VkCommandBuffer& get() noexcept { return _cmd_buffer; }

		private:
			VkCommandBuffer _cmd_buffer = VK_NULL_HANDLE;
			bool _is_recording = false;
	};
}

#endif // __AK_VK_CMD_BUFFER__
