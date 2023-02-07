// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/01/2023
// Updated : 29/01/2023

#ifndef __AK_VK_COMMAND_MANAGER__
#define __AK_VK_COMMAND_MANAGER__

#include <Akpch.h>
#include "vk_cmd_pool.h"
#include "vk_cmd_buffer.h"

namespace Ak
{
	class CmdManager
	{
		public:
			CmdManager() = default;

			void init() noexcept;
			void beginRecord(int active_image_index);
			void endRecord(int active_image_index);
			void destroy() noexcept;

			inline CmdPool& getCmdPool() noexcept { return _cmd_pool; }
			inline CmdBuffer& getCmdBuffer(int i) noexcept { return _cmd_buffers[i]; }
			
			~CmdManager() = default;

		private:
			std::array<CmdBuffer, MAX_FRAMES_IN_FLIGHT> _cmd_buffers;
			CmdPool _cmd_pool;
	};
}

#endif
