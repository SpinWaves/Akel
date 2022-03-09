// This file is a part of Akel
// Author : @kbz_8
// Created : 06/03/2022
// Updated : 09/03/2022

#include <Renderer/rendererComponent.h>
#include <Graphics/matrixes.h>

namespace Ak
{
    void RendererComponent::createDescriptorSetLayout()
    {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan UBO : failed to create descriptor set layout");
    }

    void RendererComponent::createUniformBuffers()
    {
        VkDeviceSize bufferSize;
        if(mode == RenderingMode::render3D)
            bufferSize = sizeof(UniformBufferObject3D);
        else if(mode == RenderingMode::render2D)
            bufferSize = sizeof(UniformBufferObject2D);

        uniformBuffers.resize(swapChainImages.size());
        uniformBuffersMemory.resize(swapChainImages.size());

        for(size_t i = 0; i < swapChainImages.size(); i++)
            createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
    }

    void RendererComponent::updateUniformBuffer(uint32_t currentImage)
    {
        if(mode == RenderingMode::render3D)
        {
            UniformBufferObject3D ubo;
            
            Matrixes::matrix_mode(matrix::model);
            Matrixes::load_identity();
            ubo.model = Matrixes::get_matrix(matrix::model);
            
            ubo.view = Matrixes::get_matrix(matrix::view);
            
            if(Matrixes::get_matrix(matrix::proj) == glm::mat4(1.0f))
                Matrixes::perspective(80, (float)window->size.X/window->size.Y, 0.01, 1000);
            ubo.proj = Matrixes::get_matrix(matrix::proj);
            ubo.proj[1][1] *= -1;
            Matrixes::matrix_mode(matrix::proj);
            Matrixes::load_identity();

            void* data = nullptr;
            vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
                memcpy(data, &ubo, sizeof(ubo));
            vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
            return;
        }
        if(mode == RenderingMode::render2D)
        {
            UniformBufferObject2D ubo;
            
            Matrixes::matrix_mode(matrix::model);
            Matrixes::load_identity();
            ubo.model = Matrixes::get_matrix(matrix::model);
            
            if(Matrixes::get_matrix(matrix::proj) == glm::mat4(1.0f))
                Matrixes::ortho(0.0f, (float)window->size.X, 0.0f, (float)window->size.Y);
            ubo.proj = Matrixes::get_matrix(matrix::proj);
            //ubo.proj[1][1] *= -1;
            Matrixes::matrix_mode(matrix::proj);
            Matrixes::load_identity();

            void* data = nullptr;
            vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
                memcpy(data, &ubo, sizeof(ubo));
            vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
        }
    }

    void RendererComponent::createDescriptorPool()
    {
        VkDescriptorPoolSize poolSize{};
        poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        poolSize.descriptorCount = static_cast<uint32_t>(swapChainImages.size());

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = 1;
        poolInfo.pPoolSizes = &poolSize;
        poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

        if(vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan UBO : failed to create descriptor pool");
    }

    void RendererComponent::createDescriptorSets()
    {
        std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(swapChainImages.size());
        if(vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan UBO : failed to allocate descriptor sets");

        for(size_t i = 0; i < swapChainImages.size(); i++)
        {
            VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            if(mode == RenderingMode::render3D)
                bufferInfo.range = sizeof(UniformBufferObject3D);
            else if(mode == RenderingMode::render2D)
                bufferInfo.range = sizeof(UniformBufferObject2D);

            VkWriteDescriptorSet descriptorWrite{};
            descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrite.dstSet = descriptorSets[i];
            descriptorWrite.dstBinding = 0;
            descriptorWrite.dstArrayElement = 0;
            descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrite.descriptorCount = 1;
            descriptorWrite.pBufferInfo = &bufferInfo;

            vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
        }
    }
}
