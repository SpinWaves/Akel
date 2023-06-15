// This file is a part of Akel
// Authors : @kbz_8
// Created : 22/12/2022
// Updated : 15/06/2023

#include <Renderer/Images/vk_image.h>
#include <Renderer/Buffers/vk_buffer.h>
#include <Utils/assert.h>
#include <Core/core.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Command/vk_cmd_pool.h>
#include <Renderer/Command/vk_cmd_buffer.h>

namespace Ak
{
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
	{
		for(VkFormat format : candidates)
		{
			VkFormatProperties props;
			vkGetPhysicalDeviceFormatProperties(Render_Core::get().getDevice().getPhysicalDevice(), format, &props);
			if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
				return format;
			else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
				return format;
		}

		Core::log::report(FATAL_ERROR, "Vulkan : failed to find image format");
	}

	bool isDepthFormat(VkFormat format)
	{
		switch(format)
		{
			case VK_FORMAT_D16_UNORM:
			case VK_FORMAT_D32_SFLOAT:
			case VK_FORMAT_D32_SFLOAT_S8_UINT:
			case VK_FORMAT_D24_UNORM_S8_UINT:
			case VK_FORMAT_D16_UNORM_S8_UINT:
				return true;
		}
		return false;
	}

	bool isStencilFormat(VkFormat format)
	{
		switch(format)
		{
			case VK_FORMAT_D32_SFLOAT_S8_UINT:
			case VK_FORMAT_D24_UNORM_S8_UINT:
				return true;
		}
		return false;
	}

	VkPipelineStageFlags layoutToAccessMask(VkImageLayout layout, bool isDestination)
	{
		VkPipelineStageFlags accessMask = 0;

		switch(layout)
		{
			case VK_IMAGE_LAYOUT_UNDEFINED:
				if(isDestination)
					Core::log::report(ERROR, "Vulkan : the new layout used in a transition must not be VK_IMAGE_LAYOUT_UNDEFINED");
			break;
			case VK_IMAGE_LAYOUT_GENERAL: accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT; break;
			case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL: accessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT; break;
			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL: accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT; break;
			case VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
				accessMask = VK_ACCESS_SHADER_READ_BIT; // VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
			break;
			case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL: accessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT; break;
			case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL: accessMask = VK_ACCESS_TRANSFER_READ_BIT; break;
			case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: accessMask = VK_ACCESS_TRANSFER_WRITE_BIT; break;
			case VK_IMAGE_LAYOUT_PREINITIALIZED:
				if(!isDestination)
					accessMask = VK_ACCESS_HOST_WRITE_BIT;
				else
					Core::log::report(ERROR, "Vulkan : the new layout used in a transition must not be VK_IMAGE_LAYOUT_PREINITIALIZED");
			break;
			case VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL: accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT; break;
			case VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL: accessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT; break;
			case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR: accessMask = VK_ACCESS_MEMORY_READ_BIT; break;

			default: Core::log::report(ERROR, "Vulkan : unexpected image layout"); break;
		}

		return accessMask;
	}

	VkPipelineStageFlags accessFlagsToPipelineStage(VkAccessFlags accessFlags, VkPipelineStageFlags stageFlags)
	{
		VkPipelineStageFlags stages = 0;

		while(accessFlags != 0)
		{
			VkAccessFlagBits AccessFlag = static_cast<VkAccessFlagBits>(accessFlags & (~(accessFlags - 1)));
			Ak_assert(AccessFlag != 0 && (AccessFlag & (AccessFlag - 1)) == 0, "Error");
			accessFlags &= ~AccessFlag;

			switch(AccessFlag)
			{
				case VK_ACCESS_INDIRECT_COMMAND_READ_BIT: stages |= VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT; break;
				case VK_ACCESS_INDEX_READ_BIT: stages |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT; break;
				case VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT: stages |= VK_PIPELINE_STAGE_VERTEX_INPUT_BIT; break;
				case VK_ACCESS_UNIFORM_READ_BIT: stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT; break;
				case VK_ACCESS_INPUT_ATTACHMENT_READ_BIT: stages |= VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; break;
				case VK_ACCESS_SHADER_READ_BIT: stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT; break;
				case VK_ACCESS_SHADER_WRITE_BIT: stages |= stageFlags | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT; break;
				case VK_ACCESS_COLOR_ATTACHMENT_READ_BIT: stages |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT; break;
				case VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT: stages |= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT; break;
				case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT: stages |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT; break;
				case VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT: stages |= VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT; break;
				case VK_ACCESS_TRANSFER_READ_BIT: stages |= VK_PIPELINE_STAGE_TRANSFER_BIT; break;
				case VK_ACCESS_TRANSFER_WRITE_BIT: stages |= VK_PIPELINE_STAGE_TRANSFER_BIT; break;
				case VK_ACCESS_HOST_READ_BIT: stages |= VK_PIPELINE_STAGE_HOST_BIT; break;
				case VK_ACCESS_HOST_WRITE_BIT: stages |= VK_PIPELINE_STAGE_HOST_BIT; break;
				case VK_ACCESS_MEMORY_READ_BIT: break;
				case VK_ACCESS_MEMORY_WRITE_BIT: break;

				default: Core::log::report(ERROR, "Vulkan : unknown access flag"); break;
			}
		}
		return stages;
	}

	void Image::create(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties)
	{
		_width = width;
		_height = height;
		_format = format;

		VkImageCreateInfo imageInfo{};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageInfo.imageType = VK_IMAGE_TYPE_2D;
		imageInfo.extent.width = width;
		imageInfo.extent.height = height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = format;
		imageInfo.tiling = tiling;
		imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		imageInfo.usage = usage;
		imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		_layout = VK_IMAGE_LAYOUT_UNDEFINED;

		if(vkCreateImage(Render_Core::get().getDevice().get(), &imageInfo, nullptr, &_image) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create an image");

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(Render_Core::get().getDevice().get(), _image, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = RCore::findMemoryType(memRequirements.memoryTypeBits, properties);

		if(vkAllocateMemory(Render_Core::get().getDevice().get(), &allocInfo, nullptr, &_memory) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate memory for an image");

		vkBindImageMemory(Render_Core::get().getDevice().get(), _image, _memory, 0);
	}

	void Image::createImageView(VkImageViewType type, VkImageAspectFlags aspectFlags) noexcept
	{
		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = _image;
		viewInfo.viewType = type;
		viewInfo.format = _format;
		viewInfo.subresourceRange.aspectMask = aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		if(vkCreateImageView(Render_Core::get().getDevice().get(), &viewInfo, nullptr, &_image_view) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create image view");
	}

	void Image::createSampler() noexcept
	{
		VkSamplerCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		info.magFilter = VK_FILTER_LINEAR;
		info.minFilter = VK_FILTER_LINEAR;
		info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		info.minLod = -1000;
		info.maxLod = 1000;
		info.anisotropyEnable = VK_FALSE;
		info.maxAnisotropy = 1.0f;

		if(vkCreateSampler(Render_Core::get().getDevice().get(), &info, nullptr, &_sampler) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan Texture : unable to create image sampler");
	}

	void Image::transitionLayout(VkImageLayout new_layout, CmdBuffer& cmd)
	{
		cmd.reset();
		cmd.beginRecord();

		VkImageMemoryBarrier barrier{};
		barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		barrier.oldLayout = _layout;
		barrier.newLayout = new_layout;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.image = _image;
		barrier.subresourceRange.aspectMask = isDepthFormat(_format) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 1;
		barrier.srcAccessMask = layoutToAccessMask(_layout, false);
        barrier.dstAccessMask = layoutToAccessMask(new_layout, true);
		if(isStencilFormat(_format))
        	barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;

		VkPipelineStageFlags sourceStage = 0;
		if(barrier.oldLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
			sourceStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		else if(barrier.srcAccessMask != 0)
			sourceStage = accessFlagsToPipelineStage(barrier.srcAccessMask, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
		else
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

		VkPipelineStageFlags destinationStage = 0;
		if(barrier.newLayout == VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
			destinationStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		else if(barrier.dstAccessMask != 0)
			destinationStage = accessFlagsToPipelineStage(barrier.dstAccessMask, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
		else
			destinationStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

		vkCmdPipelineBarrier(cmd.get(), sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

		cmd.endRecord();
		cmd.submitIdle();
		_layout = new_layout;
	}

	void Image::copyBuffer(Buffer& buffer)
	{
		CmdPool cmdpool;
		cmdpool.init();
		auto device = Render_Core::get().getDevice().get();

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = cmdpool.get();
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer cmdBuffer;
		vkAllocateCommandBuffers(device, &allocInfo, &cmdBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(cmdBuffer, &beginInfo);

		VkImageMemoryBarrier copy_barrier = {};
		copy_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		copy_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		copy_barrier.oldLayout = _layout;
		copy_barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		copy_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		copy_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		copy_barrier.image = _image;
		copy_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		copy_barrier.subresourceRange.levelCount = 1;
		copy_barrier.subresourceRange.layerCount = 1;
		vkCmdPipelineBarrier(cmdBuffer, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &copy_barrier);

		VkBufferImageCopy region = {};
		region.bufferOffset = 0;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;
		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = 0;
		region.imageSubresource.layerCount = 1;
		region.imageOffset = {0, 0, 0};
		region.imageExtent = {
			_width,
			_height,
			1
		};
		vkCmdCopyBufferToImage(cmdBuffer, buffer.get(), _image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

		VkImageMemoryBarrier use_barrier = {};
		use_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		use_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		use_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		use_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		use_barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		use_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		use_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		use_barrier.image = _image;
		use_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		use_barrier.subresourceRange.levelCount = 1;
		use_barrier.subresourceRange.layerCount = 1;
		vkCmdPipelineBarrier(cmdBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &use_barrier);

		vkEndCommandBuffer(cmdBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &cmdBuffer;

		auto graphicsQueue = Render_Core::get().getQueue().getGraphic();

		vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(graphicsQueue);

		cmdpool.destroy();

		_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	}

	void Image::destroy() noexcept
	{
		if(_sampler != VK_NULL_HANDLE)
			vkDestroySampler(Render_Core::get().getDevice().get(), _sampler, nullptr);
		
		if(_image_view != VK_NULL_HANDLE)
			vkDestroyImageView(Render_Core::get().getDevice().get(), _image_view, nullptr);
		
		Ak_assert(_memory != VK_NULL_HANDLE, "trying to destroy an uninit memory for an image");
	    vkFreeMemory(Render_Core::get().getDevice().get(), _memory, nullptr);

		Ak_assert(_image != VK_NULL_HANDLE, "trying to destroy an uninit vulkan image");
		vkDestroyImage(Render_Core::get().getDevice().get(), _image, nullptr);
	}
}
