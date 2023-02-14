// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 14/02/2023

#include <Renderer/Pipeline/vk_graphic_pipeline.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Images/texture.h>
#include <Graphics/vertex.h>

namespace Ak
{
	void GraphicPipeline::init(class RendererComponent& renderer, std::vector<std::vector<uint32_t>> shaders, const PipelineDesc& desc)
    {
		std::vector<VkPipelineShaderStageCreateInfo> stages;
		std::vector<VkDescriptorSetLayout> descriptor_layouts;

		for(int i = 0; i < shaders.size(); i++)
		{
			_shaders.emplace_back(std::move(shaders[i]), &renderer);
			_shaders.back().generate();

			if(textures.empty())
			{
				if(_shaders.back().getImageSamplers().count("texSampler"))
				{
					_dummy = create_Unique_ptr<Texture>();
					std::array<uint8_t, 4> pixel = { 255, 255, 255, 255 };
					_dummy->create(pixel.data(), 1, 1, VK_FORMAT_R8G8B8A8_UNORM);
					_dummy->setShaderInterface(_shaders.back());
				}
			}
			else
				desc.main_texture->setShaderInterface(_shaders.back());

			_shaders.back().createSets();

			VkPipelineShaderStageCreateInfo shaderStageInfo{};
			shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStageInfo.stage = _shaders.back().getType();
			shaderStageInfo.module = _shaders.back().getShaderModule();
			shaderStageInfo.pName = _shaders.back().get_entry_point_name().c_str();

			stages.push_back(shaderStageInfo);
			for(DescriptorSetLayout& desc : _shaders.back().getDescriptorSetLayouts())
				descriptor_layouts.push_back(desc.get());
		}

		VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{};
		vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
		vertexInputStateCreateInfo.pVertexBindingDescriptions = &Vertex::getBindingDescriptions();
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = 3;
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = Vertex::getAttributeDescriptions().data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = desc.topology;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkDynamicState states[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

		constexpr size_t statesCount = sizeof(states) / sizeof(VkDynamicState);
		VkPipelineDynamicStateCreateInfo dynamicStates{};
		dynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStates.dynamicStateCount = statesCount;
		dynamicStates.pDynamicStates = states;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)renderer.getSwapChain()._swapChainExtent.width;
        viewport.height = (float)renderer.getSwapChain()._swapChainExtent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = renderer.getSwapChain()._swapChainExtent;

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
        rasterizer.polygonMode = desc.mode;
        rasterizer.lineWidth = desc.line_width;
        rasterizer.cullMode = desc.culling;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineDepthStencilStateCreateInfo depthStencil{};
        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        depthStencil.depthTestEnable = VK_TRUE;
        depthStencil.depthWriteEnable = VK_TRUE;
        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        depthStencil.depthBoundsTestEnable = VK_FALSE;
        depthStencil.stencilTestEnable = VK_FALSE;

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
        pipelineInfo.renderPass = renderer.getRenderPass().get();
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.pDepthStencilState = &depthStencil;

        if(vkCreateGraphicsPipelines(Render_Core::get().getDevice().get(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline) != VK_SUCCESS)
            Core::log::report(FATAL_ERROR, "Vulkan : failed to create a graphics pipeline");

		if(!_shaders.empty())
		{
			for(Shader& shader : _shaders)
				shader.destroyModule();
		}
    }

    void GraphicPipeline::destroy() noexcept
    {
        Ak_assert(_graphicsPipeline != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
        vkDestroyPipeline(Render_Core::get().getDevice().get(), _graphicsPipeline, nullptr);
        
		if(!_shaders.empty())
		{
			for(Shader& shader : _shaders)
				shader.destroy();
		}

		if(_dummy)
		{
			_dummy->destroy();
			_dummy.reset(nullptr);
		}

        Ak_assert(_pipelineLayout != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
		vkDestroyPipelineLayout(Render_Core::get().getDevice().get(), _pipelineLayout, nullptr);
    }
}
