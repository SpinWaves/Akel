// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/12/2022
// Updated : 10/02/2023

#ifndef __AK_VK_IMAGE__
#define __AK_VK_IMAGE__

#include <Akpch.h>
#include <Renderer/Descriptors/vk_descriptor_set.h>

namespace Ak
{
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	class Image
	{
		friend class GraphicsPipeline;

		public:
			Image() = default;

			void create(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
			void copyBuffer(class Buffer& buffer);
			void destroy() noexcept;

			inline VkImage& get() noexcept { return _image; }
			inline VkImage& operator()() noexcept { return _image; }
			inline VkDeviceMemory getDeviceMemory() noexcept { return _memory; }
			inline VkImageView& getImageView() noexcept { return _image_view; }
			inline VkFormat& getFormat() noexcept { return _format; }
			inline VkSampler& getSampler() noexcept { return _sampler; }

			virtual ~Image() = default;

		protected:
			void createImageView(VkImageViewType type, VkImageAspectFlags aspectFlags) noexcept;
			void createSampler() noexcept;

		private:
			DescriptorSet _desc;
			VkImage _image = VK_NULL_HANDLE;
			VkDeviceMemory _memory = VK_NULL_HANDLE;
			VkImageView _image_view = VK_NULL_HANDLE;
			VkSampler _sampler = VK_NULL_HANDLE;
			VkFormat _format;
			uint32_t _width = 0;
			uint32_t _height = 0;
	};
}

#endif
