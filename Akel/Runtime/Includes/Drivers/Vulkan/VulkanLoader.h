// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_LOADER_H
#define AK_VULKAN_LOADER_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Core/OS/LibLoader.h>

namespace Ak
{
	class AK_VULKAN_API VulkanLoader
	{
		public:
			VulkanLoader(class VulkanRenderer& renderer);
			~VulkanLoader();

		private:
			void LoadGlobal(class VulkanRenderer& renderer);

		private:
			LibModule m_vulkan_lib = NullModule;
	};
}

#endif
