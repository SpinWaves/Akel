/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vk_graphic_pipeline.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maldavid <kbz_8.dev@akel-engine.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:47:24 by maldavid          #+#    #+#             */
/*   Updated: 2023/06/17 09:23:00 by maldavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This file is a part of Akel
// Authors : @kbz_8
// Created : 04/04/2022
// Updated : 15/06/2023

#include <Renderer/Pipeline/vk_graphic_pipeline.h>
#include <Renderer/Core/render_core.h>
#include <Utils/assert.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Images/texture.h>
#include <Graphics/vertex.h>
#include <Renderer/Pipeline/shaders_library.h>
#include <Renderer/RenderPass/render_pass_library.h>
#include <Renderer/RenderPass/frame_buffer_library.h>
#include <Renderer/Images/texture_library.h>

namespace Ak
{
	bool PipelineDesc::operator==(const PipelineDesc& other) noexcept
	{
		bool same_shaders = true;
		for(int i = 0; i < shaders.size(); i++)
		{
			if(shaders.size() != other.shaders.size())
			{
				same_shaders = false;
				break;
			}
			if(ShadersLibrary::get().getShader(shaders[i])->_byte_code != ShadersLibrary::get().getShader(other.shaders[i])->_byte_code)
				same_shaders = false;
		}
		return	(culling == other.culling) && (mode == other.mode) && (topology == other.topology) &&
				(line_width == other.line_width) && same_shaders && (swapchain == other.swapchain) &&
				(clear_color == other.clear_color) && (clear_target = other.clear_target);
	}

	void GraphicPipeline::createFrameBuffers()
	{
		std::vector<RenderPassAttachement> attachements;
		_frame_buffers.clear();

		if(_desc.swapchain)
			attachements.emplace_back(&_renderer->getSwapChain().getImage(0), ImageType::color);
		else
		{
			for(TextureID texture : _desc.render_targets)
			{
				if(texture != nulltexture)
					attachements.emplace_back(TextureLibrary::get().getTexture(texture).get(), ImageType::color);
			}
		}

		if(_desc.depth != nullptr)
			attachements.emplace_back(_desc.depth, ImageType::depth);

		RenderPassDesc render_pass_desc{};
		render_pass_desc.clear = _desc.clear_target;
		render_pass_desc.attachements = attachements;
		_render_pass = RenderPassesLibrary::get().getRenderPass(render_pass_desc);

		FrameBufferDesc fbdesc{};
		fbdesc.render_pass = _render_pass;
		fbdesc.renderer = _renderer;

		if(_desc.swapchain)
		{
			for(std::size_t i = 0; i < _renderer->getSwapChain().getImagesNumber(); i++)
			{
				attachements[0].image = &_renderer->getSwapChain().getImage(i);
				fbdesc.screen_fbo = true;
				fbdesc.attachements = attachements;
				fbdesc.width = _renderer->getSwapChain().getImage(i).getWidth();
				fbdesc.height = _renderer->getSwapChain().getImage(i).getHeight();
				_frame_buffers.emplace_back(FrameBufferLibrary::get().getFrameBuffer(fbdesc));
			}
		}
		else
		{
			fbdesc.screen_fbo = false;
			fbdesc.attachements = attachements;
			fbdesc.width = attachements[0].image->getWidth();
			fbdesc.height = attachements[0].image->getHeight();
			_frame_buffers.emplace_back(FrameBufferLibrary::get().getFrameBuffer(fbdesc));
		}
	}

	void GraphicPipeline::transitionAttachements()
	{
		if(_desc.depth != nullptr)
			_desc.depth->transitionLayout(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, *_renderer->getSingleTimeCmdBuffer());
	}

	void GraphicPipeline::init(class RendererComponent* renderer, PipelineDesc& desc)
	{
		_renderer = renderer;
		_desc = desc;

		std::vector<VkPipelineShaderStageCreateInfo> stages;
		std::vector<VkDescriptorSetLayout> descriptor_layouts;
		std::vector<VkPushConstantRange> pc_ranges;

		transitionAttachements();
		createFrameBuffers();

		for(int i = 0; i < desc.shaders.size(); i++)
		{
			auto shader = ShadersLibrary::get().getShader(desc.shaders[i]);
			shader->generate();

			VkPipelineShaderStageCreateInfo shaderStageInfo{};
			shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStageInfo.stage = shader->getType();
			shaderStageInfo.module = shader->getShaderModule();
			shaderStageInfo.pName = shader->getEntryPointName().c_str();

			stages.push_back(shaderStageInfo);
			for(DescriptorSetLayout& descriptor : shader->getDescriptorSetLayouts())
				descriptor_layouts.push_back(descriptor.get());

			for(auto& [name, pc] : shader->getPushConstants())
			{
				VkPushConstantRange push_constant;
				push_constant.offset = pc.getOffset();
				push_constant.size = pc.getSize();
				push_constant.stageFlags = shader->getType();
				pc_ranges.push_back(push_constant);
			}
		}

		VkVertexInputBindingDescription binding_description = Vertex::getBindingDescription();
		std::array<VkVertexInputAttributeDescription, 3> attributes_description = Vertex::getAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{};
		vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = 1;
		vertexInputStateCreateInfo.pVertexBindingDescriptions = &binding_description;
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = attributes_description.size();
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = attributes_description.data();

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

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = nullptr;
		viewportState.scissorCount = 1;
		viewportState.pScissors = nullptr;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = desc.mode;
		rasterizer.lineWidth = desc.line_width;
		rasterizer.cullMode = desc.culling;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
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
		pipelineLayoutInfo.pushConstantRangeCount = pc_ranges.size();
		pipelineLayoutInfo.pPushConstantRanges = pc_ranges.data();

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
		pipelineInfo.renderPass = _render_pass->get();
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.pDepthStencilState = &depthStencil;

		if(vkCreateGraphicsPipelines(Render_Core::get().getDevice().get(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : failed to create a graphics pipeline");
	}

	void GraphicPipeline::bindPipeline(CmdBuffer& commandBuffer) noexcept
	{
		std::shared_ptr<FrameBuffer> fb;
		if(_renderer->isFrameBufferResizeRequested())
		{
			destroy();
			init(_renderer, _desc);
		}
		if(!_renderer->isRendering())
			return;
		if(_desc.swapchain)
			fb = _frame_buffers[_renderer->getSwapChainImageIndex()];
		else
			fb = _frame_buffers[0];

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = fb->getWidth();
		viewport.height = fb->getHeight();
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer.get(), 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent.width = fb->getWidth();
		scissor.extent.height = fb->getHeight();
		vkCmdSetScissor(commandBuffer.get(), 0, 1, &scissor);

		vkCmdBindPipeline(commandBuffer.get(), getPipelineBindPoint(), getPipeline());

		_render_pass->begin(commandBuffer, _desc.clear_color, *(fb.get()), fb->getWidth(), fb->getHeight());
	}

	void GraphicPipeline::endPipeline(CmdBuffer& commandBuffer) noexcept
	{
		if(!_renderer->isRendering())
			return;
		_render_pass->end(commandBuffer);
	}

	void GraphicPipeline::destroy() noexcept
	{
		Ak_assert(_graphicsPipeline != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
		vkDestroyPipeline(Render_Core::get().getDevice().get(), _graphicsPipeline, nullptr);
		Ak_assert(_pipelineLayout != VK_NULL_HANDLE, "trying to destroy an uninit pipeline");
		vkDestroyPipelineLayout(Render_Core::get().getDevice().get(), _pipelineLayout, nullptr);
	}
}
