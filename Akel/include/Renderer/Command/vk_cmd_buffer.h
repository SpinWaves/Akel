// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/04/2022
// Updated : 26/09/2023

#ifndef __AK_VK_CMD_BUFFER__
#define __AK_VK_CMD_BUFFER__

#include <Akpch.h>
#include <Renderer/Core/vk_fence.h>

namespace Ak
{
	class CmdBuffer
	{
		public:
			void init(class CmdManager& manager, bool is_single_time = true);
			void init(class CmdPool* manager, bool is_single_time = true);
			void destroy() noexcept;

			void beginRecord(VkCommandBufferUsageFlags usage = 0);
			void submit(class Semaphore& semaphores) noexcept;
			void submitIdle();
			inline bool isReadyToBeUsed() noexcept { return _fence.isReady(); }
			inline void waitForExecution() noexcept { _fence.wait(); }
			inline void reset() noexcept { vkResetCommandBuffer(_cmd_buffer, 0); _fence.reset(); }
			void endRecord();

			inline bool isRecording() const noexcept { return _is_recording; }
			inline bool isInit() const noexcept { return _cmd_buffer != VK_NULL_HANDLE; }

			inline VkCommandBuffer& operator()() noexcept { return _cmd_buffer; }
			inline VkCommandBuffer& get() noexcept { return _cmd_buffer; }

		private:
			Fence _fence;
			VkCommandBuffer _cmd_buffer = VK_NULL_HANDLE;
			class CmdPool* _pool = nullptr;
			bool _is_recording = false;
			bool _is_single_time = true;
	};
}

#endif // __AK_VK_CMD_BUFFER__
