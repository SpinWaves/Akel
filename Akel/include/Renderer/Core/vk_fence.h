// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/03/2023
// Updated : 17/06/2023

#ifndef __AK_VK_CPU_FENCE__
#define __AK_VK_CPU_FENCE__

#include <Akpch.h>

namespace Ak
{
	class Fence
	{
		public:
			Fence() = default;
			
			void init();
			
			inline VkFence& get() noexcept { return _fence; }
			void wait() noexcept;
			void reset() noexcept;
			bool isReady() noexcept;
			inline void waitAndReset() noexcept { wait(); reset(); }

			void destroy() noexcept;

			~Fence() = default;

		private:
			VkFence _fence = VK_NULL_HANDLE;
	};
}

#endif
