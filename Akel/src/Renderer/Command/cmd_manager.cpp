// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/01/2023
// Updated : 17/06/2023

#include <Renderer/Command/cmd_manager.h>

namespace Ak
{
	void CmdManager::init() noexcept
	{
		_cmd_pool.init();

		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_cmd_buffers[i].init(*this, false);
		for(int i = 0; i < SINGLE_TIME_CMD_RESERVE; i++)
			_single_times[i].init(*this, true);
	}

	void CmdManager::beginRecord(int active_image_index)
	{
		_cmd_buffers[active_image_index].beginRecord();
	}

	CmdBuffer* CmdManager::getSingleTimeBuffer() noexcept
	{
		for(int i = 0; i < SINGLE_TIME_CMD_RESERVE; i++)
		{
			if(_single_times[i].isReadyToBeUsed())
				return &_single_times[i];
		}
		return nullptr;
	}

	void CmdManager::endRecord(int active_image_index)
	{
		_cmd_buffers[active_image_index].endRecord();
	}

	void CmdManager::destroy() noexcept
	{
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			_cmd_buffers[i].destroy();
		for(int i = 0; i < SINGLE_TIME_CMD_RESERVE; i++)
			_single_times[i].destroy();
		_cmd_pool.destroy();
	}
}
