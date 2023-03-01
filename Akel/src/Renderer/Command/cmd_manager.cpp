// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/01/2023
// Updated : 01/03/2023

#include <Renderer/Command/cmd_manager.h>

namespace Ak
{
	void CmdManager::init() noexcept
	{
		_cmd_pool.init();

		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_cmd_buffers[i].init(this);
	}

	void CmdManager::beginRecord(int active_image_index)
	{
		_cmd_buffers[active_image_index].beginRecord();
	}

	void CmdManager::endRecord(int active_image_index)
	{
		_cmd_buffers[active_image_index].endRecord();
	}

	void CmdManager::destroy() noexcept
	{
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_cmd_buffers[i].destroy();
		_cmd_pool.destroy();
	}
}
