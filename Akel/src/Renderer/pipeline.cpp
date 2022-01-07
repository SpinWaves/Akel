// This file is a part of Akel
// Author : @kbz_8
// Created : 05/06/2021
// Updated : 05/03/2022

#include <Renderer/rendererComponent.h>
#include <Core/core.h>
#include <Modules/GLSL/GLSL_compiler.h>

namespace Ak
{
	void RendererComponent::useShader(shader internal)
	{
		switch(internal)
		{
			case shader::basic_2D : 
				_vertexShader = Core::getShaderPath() + "basic_2D/basic_2D.vert";
				_fragmentShader = Core::getShaderPath() + "basic_2D/basic_2D.frag";
			break;

			case shader::basic_3D : Core::log::report(MESSAGE, "Renderer Component : there are no basic 3D shader yet"); break;

			default : Core::log::report(FATAL_ERROR, "Renderer Component : unable to find internal shader"); return;
		}
	}

    void RendererComponent::createGraphicsPipeline()
    {
		if(_vertexShader.empty())
			Core::log::report(FATAL_ERROR, "Renderer Component Pipeline : no vertex shader given");
		if(_fragmentShader.empty())
			Core::log::report(FATAL_ERROR, "Renderer Component Pipeline : no fragment shader given");

		VkShaderModule vertShaderModule = createShaderModule(GLSL_Compiler::compileToSPIRV(GLSL::vertex, _vertexShader, true));
	    VkShaderModule fragShaderModule = createShaderModule(GLSL_Compiler::compileToSPIRV(GLSL::fragment, _fragmentShader, true));

	    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	    vertShaderStageInfo.module = vertShaderModule;
	    vertShaderStageInfo.pName = "main";

	    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	    fragShaderStageInfo.module = fragShaderModule;
	    fragShaderStageInfo.pName = "main";

	    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

	    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	    vertexInputInfo.vertexBindingDescriptionCount = 0;
	    vertexInputInfo.vertexAttributeDescriptionCount = 0;
	    auto bindingDescription = Vertex2D::getBindingDescription();
	    auto attributeDescriptions = Vertex2D::getAttributeDescriptions();

	    vertexInputInfo.vertexBindingDescriptionCount = 1;
	    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();


	    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	    inputAssembly.primitiveRestartEnable = VK_FALSE;

	    VkViewport viewport{};
	    viewport.x = 0.0f;
	    viewport.y = 0.0f;
	    viewport.width = (float) swapChainExtent.width;
	    viewport.height = (float) swapChainExtent.height;
	    viewport.minDepth = 0.0f;
	    viewport.maxDepth = 1.0f;

	    VkRect2D scissor{};
	    scissor.offset = {0, 0};
	    scissor.extent = swapChainExtent;

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
	    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	    rasterizer.lineWidth = 1.0f;
	    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
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
	    pipelineLayoutInfo.setLayoutCount = 0;
	    pipelineLayoutInfo.pushConstantRangeCount = 0;

	    if(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to create pipeline layout");

		VkGraphicsPipelineCreateInfo pipelineInfo{};
	    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	    pipelineInfo.stageCount = 2;
	    pipelineInfo.pStages = shaderStages;
	    pipelineInfo.pVertexInputState = &vertexInputInfo;
	    pipelineInfo.pInputAssemblyState = &inputAssembly;
	    pipelineInfo.pViewportState = &viewportState;
	    pipelineInfo.pRasterizationState = &rasterizer;
	    pipelineInfo.pMultisampleState = &multisampling;
	    pipelineInfo.pColorBlendState = &colorBlending;
	    pipelineInfo.layout = pipelineLayout;
	    pipelineInfo.renderPass = renderPass;
	    pipelineInfo.subpass = 0;
	    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	    if(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to create graphics pipeline");

        vkDestroyShaderModule(device, fragShaderModule, nullptr);
        vkDestroyShaderModule(device, vertShaderModule, nullptr);
    }

    VkShaderModule RendererComponent::createShaderModule(const std::vector<uint32_t>& code)
    {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size() * 4; // times 4 because codeSize takes size in bytes, not uint32_ts
        createInfo.pCode = code.data();

        VkShaderModule shaderModule;
        if(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
			Core::log::report(FATAL_ERROR, "Vulkan : Failed to create shader module");

        return std::move(shaderModule);
    }
}
