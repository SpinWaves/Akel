// This file is a part of Akel
// Authors : @kbz_8
// Created : 25/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_INSTANCE__
#define __AK_VK_INSTANCE__

#include <Akpch.h>

namespace Ak
{
	class WindowComponent;

	class Instance
	{
		public:
			Instance(WindowComponent* window);

			friend VKAPI_ATTR VkBool32 VKAPI_CALL callbackDebug(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData);

			static VkResult fvkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger);
			static void fvkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks *pAllocator);
			static void fvkCmdPushDescriptorSetKHR(VkDevice device, VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites);
			static uint32_t findMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties *deviceMemoryProperties, const VkMemoryRequirements *memoryRequirements, VkMemoryPropertyFlags requiredProperties);

			inline operator const VkInstance& () const { return instance; }

			inline constexpr bool areValidationLayersEnabled() const noexcept { return _enableValidationLayers; }
			const VkInstance& getInstance() const noexcept { return instance; }

			inline WindowComponent* getHandledWindow() const noexcept { return _window; }

			static const std::vector<const char*> validationLayers;

			~Instance();

		private:
			bool checkValidationLayerSupport() const;
			std::vector<const char*> getExtensions() const;
			void createInstance();
			void createDebugMessenger();

			static void logVulkanLayers(const std::vector<VkLayerProperties>& layerProperties);

			#ifdef AK_DEBUG
		        constexpr const bool _enableValidationLayers = true;
		    #else
		        constexpr const bool _enableValidationLayers = false;
		    #endif

			VkInstance _instance = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT _debugMessenger = VK_NULL_HANDLE;
			WindowComponent* _window = nullptr;
	};
}

#endif // __AK_VK_INSTANCE__
