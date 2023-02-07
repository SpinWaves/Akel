// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 01/02/2023

#include <Renderer/Descriptors/vk_descriptor_set.h>
#include <Renderer/Descriptors/vk_descriptor_set_layout.h>
#include <Renderer/Descriptors/vk_descriptor_pool.h>
#include <Renderer/Buffers/vk_ubo.h>
#include <Renderer/Core/render_core.h>
#include <Renderer/Pipeline/vk_shader.h>
#include <Renderer/rendererComponent.h>
#include <Utils/assert.h>

namespace Ak
{
    void DescriptorSet::init(RendererComponent* renderer, UBO* ubo, DescriptorSetLayout& layout, DescriptorPool& pool)
    {
		_renderer = renderer;

        auto device = Render_Core::get().getDevice().get();

		_pool = pool.get();

		std::array<VkDescriptorSetLayout, MAX_FRAMES_IN_FLIGHT> layouts;
		layouts.fill(layout.get());

        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = _pool;
        allocInfo.descriptorSetCount = MAX_FRAMES_IN_FLIGHT;
        allocInfo.pSetLayouts = layouts.data();

        if(vkAllocateDescriptorSets(device, &allocInfo, _desc_set.data()) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate descriptor set");

		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = ubo->get(i);
			bufferInfo.offset = ubo->getOffset(i);
			bufferInfo.range = ubo->getSize(i);

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = _desc_set[i];
			descriptorWrite.dstBinding = layout.getBinding();
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = layout.getType();
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pBufferInfo = &bufferInfo;

			vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
		}
    }

    void DescriptorSet::init(RendererComponent* renderer, VkImageView image_view, VkSampler sampler, DescriptorSetLayout& layout, DescriptorPool& pool)
	{
		_renderer = renderer;

        auto device = Render_Core::get().getDevice().get();

		_pool = pool.get();

		std::array<VkDescriptorSetLayout, MAX_FRAMES_IN_FLIGHT> layouts;
		layouts.fill(layout.get());

        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = _pool;
        allocInfo.descriptorSetCount = MAX_FRAMES_IN_FLIGHT;
        allocInfo.pSetLayouts = layouts.data();

        if(vkAllocateDescriptorSets(device, &allocInfo, _desc_set.data()) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate descriptor set");

		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = image_view;
            imageInfo.sampler = sampler;

			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = _desc_set[i];
			descriptorWrite.dstBinding = layout.getBinding();
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = layout.getType();
			descriptorWrite.descriptorCount = 1;
			descriptorWrite.pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
		}
	}

	VkDescriptorSet& DescriptorSet::operator()() noexcept
	{
		return _desc_set[_renderer->getActiveImageIndex()];
	}
	VkDescriptorSet& DescriptorSet::get() noexcept
	{
		return _desc_set[_renderer->getActiveImageIndex()];
	}

    void DescriptorSet::destroy() noexcept
    {
		for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
			Ak_assert(_desc_set[i] != VK_NULL_HANDLE, "trying to destroy an uninit descriptor set");
		vkFreeDescriptorSets(Render_Core::get().getDevice().get(), _pool, MAX_FRAMES_IN_FLIGHT, _desc_set.data());
    }
}