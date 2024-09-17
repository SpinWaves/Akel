// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_VULKAN_RENDERER__
#define __AK_VULKAN_RENDERER__

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIRenderer.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Core/Memory/UniquePtr.h>

namespace Ak
{
	[[nodiscard]]
	const char* VerbaliseVkResult(VkResult result) noexcept;

	class AK_VULKAN_API VulkanRenderer : public RHIRenderer
	{
		public:
			VulkanRenderer();

			inline VulkanDevice& GetDevice() override;
			//inline static VulkanInstance& GetInstance();

			~VulkanRenderer() override;

		private:
			//static UniquePtr<VulkanInstance> p_instance;
			UniquePtr<VulkanDevice> p_device;
	};

	inline bool IsVulkanSupported() noexcept;
}

#include <Drivers/Vulkan/VulkanRenderer.inl>

#endif
