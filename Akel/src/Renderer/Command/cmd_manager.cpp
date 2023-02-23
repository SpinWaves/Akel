// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/01/2023
// Updated : 23/02/2023

#include <Renderer/Command/cmd_manager.h>

namespace Ak
{
	void CmdManager::init() noexcept
	{
		_cmd_pool.init();

		for(int i = 0; i < COMMAND_BUFFERS_SETS; i++)
			for(int j = 0; j < MAX_FRAMES_IN_FLIGHT; j++)
				_cmd_buffers[i].set[j].init(this);
	}

	void CmdManager::beginRecord(int active_image_index, CmdSet set)
	{
		_cmd_buffers[static_cast<uint32_t>(set)].set[active_image_index].beginRecord();
	}

	void CmdManager::endRecord(int active_image_index, CmdSet set)
	{
		_cmd_buffers[static_cast<uint32_t>(set)].set[active_image_index].endRecord();
	}

	void CmdManager::destroy() noexcept
	{
		for(int i = 0; i < COMMAND_BUFFERS_SETS; i++)
			for(int j = 0; j < MAX_FRAMES_IN_FLIGHT; j++)
				_cmd_buffers[i].set[j].destroy();
		_cmd_pool.destroy();
	}
}
