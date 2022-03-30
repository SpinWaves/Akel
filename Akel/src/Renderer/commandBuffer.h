// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_COMMAND_BUFFER__
#define __AK_VK_COMMAND_BUFFER__

#include <Akpch.h>

namespace Ak
{
	class CommandPool;
	
	class CommandBuffer
	{
		public:
			explicit CommandBuffer(bool begin = true, VkQueueFlagBits queueType = VK_QUEUE_GRAPHICS_BIT, VkCommandBufferLevel bufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

			void beginRecord();
			void endRecord();

			void pass(const VkSemaphore &waitSemaphore = VK_NULL_HANDLE, const VkSemaphore &signalSemaphore = VK_NULL_HANDLE, VkFence fence = VK_NULL_HANDLE);
			void passIdle();

			inline bool isRecodring() const noexcept { return _is_recording; }
			inline operator const VkCommandBuffer&() const noexcept { return _commandBuffer; }
			inline const VkCommandBuffer& getCommandBuffer() const noexcept { return _commandBuffer; }

			~CommandBuffer();

		private:
			VkQueue getQueue() const;

			std::shared_ptr<CommandPool> _commandPool;
			VkQueueFlagBits _queueType;
			VkCommandBuffer _commandBuffer = VK_NULL_HANDLE;
			bool _is_recording = false;
	};
}

#endif // __AK_VK_COMMAND_BUFFER__
