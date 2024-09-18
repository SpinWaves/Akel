// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_VULKAN_LOADER__
#define __AK_VULKAN_LOADER__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace Ak
{
	class AK_VULKAN_API VulkanLoader
	{
		public:
			VulkanLoader();
			~VulkanLoader();

		private:
			void LoadGlobal();

		private:
			LibModule m_vulkan_lib = NullModule;
	};
}

#endif
