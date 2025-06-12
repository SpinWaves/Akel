// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_VULKAN_RENDERER_H
#define AK_VULKAN_RENDERER_H

#include <Drivers/Vulkan/PreCompiled.h>
#include <Graphics/RHI/RHIRenderer.h>
#include <Drivers/Vulkan/VulkanInstance.h>
#include <Drivers/Vulkan/VulkanDevice.h>
#include <Drivers/Vulkan/VulkanLoader.h>
#include <Core/Memory/UniquePtr.h>

namespace Ak
{
	[[nodiscard]]
	const char* VerbaliseVkResult(VkResult result) noexcept;
	void CheckVk(VkResult result) noexcept;

	class AK_VULKAN_API VulkanRenderer : public RHIRenderer
	{
		public:
			VulkanRenderer();

			std::uint32_t LoadNewDevice(const PhysicalDeviceMinimalSpecs& specs) noexcept override;
			inline VulkanDevice& GetDevice(std::uint32_t index) override;
			inline VulkanInstance& GetInstance();

			inline static bool IsInit() noexcept;
			inline static VulkanRenderer& Get() noexcept;

			~VulkanRenderer() override;

			#define AK_VULKAN_GLOBAL_FUNCTION(fn) PFN_##fn fn = nullptr;
				#include <Drivers/Vulkan/VulkanGlobalPrototypes.h>
			#undef AK_VULKAN_GLOBAL_FUNCTION

		private:
			static VulkanRenderer* s_instance;

			VulkanLoader m_loader;
			UniquePtr<VulkanInstance> p_instance;
			std::vector<VulkanDevice> m_devices;
	};

	inline bool IsVulkanSupported() noexcept;
}

#include <Drivers/Vulkan/VulkanRenderer.inl>

#endif
