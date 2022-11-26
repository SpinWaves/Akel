// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 26/11/2022

#include "vk_graphic_pipeline.h"
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>

namespace Ak
{
	void GraphicPipeline::init(std::vector<std::vector<uint32_t>> shaders, std::vector<Shader::VertexInput> inputs,
				VkPrimitiveTopology topology, VkPolygonMode polygonMode, 
				VkCullModeFlags cullMode, VkFrontFace frontFace)
    {
		std::vector<VkPipelineShaderStageCreateInfo> stages;
		std::vector<VkDescriptorSetLayout> descriptor_layouts;

		for(int i = 0; i < shaders.size(); i++)
		{
			_shaders.push_back(memAlloc<Shader>(shaders[i]));
			_shaders.back()->generate();

			VkPipelineShaderStageCreateInfo shaderStageInfo{};
			shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStageInfo.stage = _shaders.back()->getType();
			shaderStageInfo.module = _shaders.back()->getShaderModule();
			shaderStageInfo.pName = _shaders.back()->get_entry_point_name().c_str();

			stages.push_back(shaderStageInfo);
			for(DescriptorSetLayout& desc : _shaders.back()->getDescriptorSetLayouts())
				descriptor_layouts.push_back(desc.get());
		}

		std::vector<VkVertexInputBindingDescription> bindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
		uint32_t lastAttribute = 0;

		for(const auto& input : inputs)
		{
			for(const auto& binding : input.getBindingDescriptions())
				bindingDescriptions.emplace_back(binding);

			for(const auto& attribute : input.getAttributeDescriptions())
			{
				auto &newAttribute = attributeDescriptions.emplace_back(attribute);
				newAttribute.location += lastAttribute;
			}

			if(!input.getAttributeDescriptions().empty())
				lastAttribute = attributeDescriptions.back().location + 1;
		}

		VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{};
		vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
		vertexInputStateCreateInfo.pVertexBindingDescriptions = bindingDescriptions.data();
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = topology;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkDynamicState states[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

		VkPipelineDynamicStateCreateInfo dynamicStates{};
		dynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStates.dynamicStateCount = 2;
		dynamicStates.pDynamicStates = states;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)Render_Core::get().getSwapChain()._swapChainExtent.width;
        viewport.height = (float)Render_Core::get().getSwapChain()._swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = Render_Core::get().getSwapChain()._swapChainExtent;

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = polygonMode;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = cullMode;
        rasterizer.frontFace = frontFace;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = descriptor_layouts.size();
        pipelineLayoutInfo.pSetLayouts = descriptor_layouts.data();

        if(vkCreatePipelineLayout(Render_Core::get().getDevice().get(), &pipelineLayoutInfo, nullptr, &_pipelineLayout) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create a graphics pipeline layout");

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = stages.size();
        pipelineInfo.pStages = stages.data();
        pipelineInfo.pVertexInputState = &vertexInputStateCreateInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicStates;
        pipelineInfo.layout = _pipelineLayout;
        pipelineInfo.renderPass = Render_Core::get().getRenderPass().get();
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if(vkCreateGraphicsPipelines(Render_Core::get().getDevice().get(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create a graphics pipeline");
    }

    void GraphicPipeline::destroy() noexcept
    {
        Ak_assert(_graphicsPipeline != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
        vkDestroyPipeline(Render_Core::get().getDevice().get(), _graphicsPipeline, nullptr);
        
		if(!_shaders.empty())
		{
			for(Shader* shader : _shaders)
			{
				shader->destroy();
            	memFree(shader);
			}
		}

        Ak_assert(_pipelineLayout != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
		vkDestroyPipelineLayout(Render_Core::get().getDevice().get(), _pipelineLayout, nullptr);
    }
}
