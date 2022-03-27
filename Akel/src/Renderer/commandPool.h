// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 27/03/2022

#ifndef __AK_VK_COMMAND_POOL__
#define __AK_VK_COMMAND_POOL__

#include <Akpch.h>

namespace Ak
{
	// Represents a vulkan command pool
	class CommandPool
	{
		public:
			explicit CommandPool(const std::thread::id& threadId = std::this_thread::get_id());

			inline operator const VkCommandPool& () const { return _commandPool; }

			inline const VkCommandPool& getCommandPool() const { return _commandPool; }
			inline const std::thread::id& getThreadId() const { return _threadId; }

			~CommandPool();

		private:
			VkCommandPool _commandPool = VK_NULL_HANDLE;
			std::thread::id _threadId;
	};
}

#endif // __AK_VK_COMMAND_POOL__
