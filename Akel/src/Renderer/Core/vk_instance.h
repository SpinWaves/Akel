// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/04/2022
// Updated : 07/04/2022

#ifndef __AK_VK_INSTANCE__
#define __AK_VK_INSTANCE__

#include <Akpch.h>

namespace Ak
{
	class Instance
	{
		public:

			void init();
			inline void destroy() noexcept
			{
				static_assert(_instance != VK_NULL_HANDLE, "trying to destroy an uninit instance");
				vkDestroyInstance(_instance, nullptr);
			}

			inline VkInstance& operator()() const noexcept { return _instance; }
			inline VkInstance& get() const noexcept { return _instance; }

		private:
			std::vector<const char*> getRequiredExtensions();

			VkInstance _instance = VK_NULL_HANDLE;
	};
}

#endif // __AK_VK_INSTANCE__
