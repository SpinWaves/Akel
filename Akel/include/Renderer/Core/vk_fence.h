// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/03/2023
// Updated : 01/03/2023

#ifndef __AK_VK_CPU_FENCE__
#define __AK_VK_CPU_FENCE__

#include <Akpch.h>

namespace Ak
{
	class Fence
	{
		public:
			void init();
			inline VkFence& get(int i) noexcept { return _fences[i]; }
			void destroy() noexcept;

		private:
			std::array<VkFence, MAX_FRAMES_IN_FLIGHT> _fences;
	};
}

#endif
