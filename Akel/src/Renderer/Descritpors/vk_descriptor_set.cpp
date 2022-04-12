// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/04/2022
// Updated : 12/04/2022

#include "vk_descriptor_set.h"

namespace Ak
{
    void DescriptorSet::init()
    {
        auto device = Render_Core::get().getDevice().get();

        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        if(vkAllocateDescriptorSets(device, &allocInfo, &_desc_set) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to allocate descriptor set");

        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = Render_Core::get().getUBO();
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UBO);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = _desc_set;
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
    }
}
