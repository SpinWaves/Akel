// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/01/2023
// Updated : 23/02/2023

#ifndef __AK_VK_COMMAND_MANAGER__
#define __AK_VK_COMMAND_MANAGER__

#include <Akpch.h>
#include "vk_cmd_pool.h"
#include "vk_cmd_buffer.h"

namespace Ak
{
	constexpr int COMMAND_BUFFERS_SETS = 2;

	enum class CmdSet : uint32_t
	{
		forward = 0,
		imgui = 1,
	};

	class CmdManager
	{
		friend class RendererComponent;

		public:
			CmdManager() = default;

			void init() noexcept;
			void beginRecord(int active_image_index, CmdSet set = CmdSet::forward);
			void endRecord(int active_image_index, CmdSet set = CmdSet::forward);
			void destroy() noexcept;

			inline CmdPool& getCmdPool() noexcept { return _cmd_pool; }
			inline CmdBuffer& getCmdBuffer(int i, CmdSet set = CmdSet::forward) noexcept { return _cmd_buffers[static_cast<uint32_t>(set)].set[i]; }
			
			~CmdManager() = default;

		private:
			inline CmdBuffer& getCmdBuffer(int i, int set) noexcept { return _cmd_buffers[set].set[i]; }
			
			struct CmdBufferSet
			{
				std::array<CmdBuffer, MAX_FRAMES_IN_FLIGHT> set;
			};

			std::array<CmdBufferSet, COMMAND_BUFFERS_SETS> _cmd_buffers;
			CmdPool _cmd_pool;
	};
}

#endif
