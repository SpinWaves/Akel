// This file is a part of Akel
// Authors : @kbz_8
// Created : 19/12/2022
// Updated : 19/11/2023

#ifndef __AK_VK_IMAGE__
#define __AK_VK_IMAGE__

#include <Akpch.h>
#include <Renderer/Descriptors/vk_descriptor_set.h>

namespace Ak
{
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	bool isDepthFormat(VkFormat format);
	bool isStencilFormat(VkFormat format);
	VkFormat bitsToFormat(uint32_t bits);

	enum class ImageType
	{
		color = 0,
		depth,
		depth_array,
		cube,
		other
	};

	class Image
	{
		friend class SwapChain;

		public:
			Image() = default;

			inline void create(VkImage image, VkFormat format, uint32_t width, uint32_t height, VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED) noexcept
			{
				_image = image;
				_format = format;
				_width = width;
				_height = height;
				_layout = layout;
			}
			void create(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED, bool cube = false);
			void copyBuffer(class Buffer& buffer);
			void transitionLayout(VkImageLayout new_layout, class CmdBuffer& cmd, bool submit = true);
			void destroy() noexcept;

			inline VkImage get() const noexcept { return _image; }
			inline VkImage operator()() const noexcept { return _image; }
			inline VkImageView getImageView() const noexcept { return _image_view; }
			inline VmaAllocation getAllocation() const noexcept { return _allocation; }
			inline VkFormat getFormat() const noexcept { return _format; }
			inline VkSampler getSampler() const noexcept { return _sampler; }
			inline VkImageLayout getLayout() const noexcept { return _layout; }
			inline uint32_t getWidth() const noexcept { return _width; }
			inline uint32_t getHeight() const noexcept { return _height; }

			virtual ~Image() = default;

		protected:
			void createImageView(VkImageViewType type, VkImageAspectFlags aspectFlags) noexcept;
			void createSampler() noexcept;
			void destroyImageView() noexcept;
			void destroySampler() noexcept;

		private:
			VkImage _image = VK_NULL_HANDLE;
			VmaAllocation _allocation;
			VkImageView _image_view = VK_NULL_HANDLE;
			VkSampler _sampler = VK_NULL_HANDLE;
			VkFormat _format;
			VkImageLayout _layout = VK_IMAGE_LAYOUT_UNDEFINED;
			uint32_t _width = 0;
			uint32_t _height = 0;
	};
}

namespace std
{
	template <>
	struct hash<Ak::Image>
	{
		size_t operator()(const Ak::Image& img) const noexcept
		{
			return	std::hash<VkImage>()(img.get()) +
					std::hash<VmaAllocation>()(img.getAllocation()) +
					std::hash<int>()(img.getLayout()) +
					std::hash<int>()(img.getFormat()) +
					std::hash<uint32_t>()(img.getWidth()) +
					std::hash<uint32_t>()(img.getHeight());
		}
	};
}

#endif
