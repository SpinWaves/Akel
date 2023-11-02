// This file is a part of Akel
// Authors : @maldavid
// Created : 02/11/2023
// Updated : 02/11/2023

#include <Graphics/forward_pass.h>

namespace Ak
{
	void ForwardPass::process(const RendererComponent& renderer, const ForwardPassDescription& desc)
	{
		if(desc.geometryPass)
			forwardPass(renderer, desc.fdata);
		if(desc.skyboxPass)
			skyboxPass(renderer, desc.skydata);
	}

	void ForwardPass::forwardPass(const RendererComponent& renderer, const ForwardData& data)
	{
		PipelineDesc pipeline_desc;
		pipeline_desc.shaders = data.shaders;
		pipeline_desc.clear_target = true;
		pipeline_desc.clear_color = { 0.f, 0.f, 0.f, 1.f };
		pipeline_desc.swapchain = (data.render_texture == nulltexture);
		pipeline_desc.depth = &const_cast<DepthImage&>(data.depth);
		pipeline_desc.render_targets[0] = data.render_texture;
		pipeline_desc.culling = VK_CULL_MODE_NONE;

		auto pipeline = _pipelines_manager.getPipeline(renderer, pipeline_desc);
		if(pipeline == nullptr || !pipeline->bindPipeline(renderer.getActiveCmdBuffer()))
			return;
	}

	void ForwardPass::skyboxPass(const RendererComponent& renderer, const ForwardSkyboxData& data)
	{

	}
}
