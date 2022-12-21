// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 21/12/2022

#ifndef __AK_VK_INSTANCE__
#define __AK_VK_INSTANCE__

#include <Akpch.h>

namespace Ak
{
	class Instance
	{
		public:
			void init();
			void destroy() noexcept;

			inline VkInstance& operator()() noexcept { return _instance; }
			inline VkInstance& get() noexcept { return _instance; }

		private:
			std::vector<const char*> getRequiredExtensions();
			VkInstance _instance = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_INSTANCE__
