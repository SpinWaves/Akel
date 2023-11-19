// This file is a part of Akel
// Authors : @maldavid
// Created : 02/11/2023
// Updated : 15/11/2023

#include <Graphics/forward_pass.h>
#include <Renderer/Images/texture_library.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Pipeline/vk_shader.h>
#include <Renderer/Buffers/vk_ubo.h>

namespace Ak
{
	struct MatricesBuffer
	{
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	ForwardPass::ForwardPass() {}

	void ForwardPass::init()
	{
		std::shared_ptr<Material> nullmat = create_shared_ptr_w<Material>();
		std::shared_ptr<Texture> nulltex = create_shared_ptr_w<Texture>();
		std::array<uint8_t, 4> pixel = { 255, 255, 255, 255 };
		nulltex->create(pixel.data(), 1, 1, VK_FORMAT_R8G8B8A8_UNORM);
		nullmat->_albedo = TextureLibrary::get().addTextureToLibrary(nulltex);
		MaterialLibrary::get().setNullMaterial(std::move(nullmat));
	}

	void ForwardPass::process(RendererComponent& renderer, const ForwardPassDescription& desc, bool rebuildPass)
	{
		if(desc.fdata->camera == nullptr)
		{
			Core::log::report(WARNING, "Forward Pass : no camera given, cannot render");
			return;
		}
		if(desc.fdata)
			forwardPass(renderer, *desc.fdata, rebuildPass);
		if(desc.skydata)
			skyboxPass(renderer, *desc.skydata, rebuildPass);
	}

	void ForwardPass::forwardPass(RendererComponent& renderer, const ForwardData& data, bool rebuildPass)
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

		// caches
		static std::optional<Shader::Uniform> matrices_uniform_buffer;
		static std::vector<Shader::PushConstant> push_constants;
		static std::vector<VkDescriptorSet> sets;
		static std::optional<DescriptorSet> materialset;

		if(rebuildPass)
		{
			push_constants.clear();
			sets.clear();
			sets.reserve(10); // cautional reserved size for meterial set manipulation in the forward process and prevent new allocations
			matrices_uniform_buffer = std::nullopt;
			for(ShaderID id : data.shaders)
			{
				auto shader = ShadersLibrary::get().getShader(id);
				if(!matrices_uniform_buffer)
					matrices_uniform_buffer = shader->getUniform("matrices");
				if(!materialset)
					materialset = shader->getDescriptorSetContaining("u_albedo_map");
				for(const DescriptorSet& set : shader->getDescriptorSets())
				{
					if(materialset && set.getIndex() == materialset->getIndex())
						continue;
					sets.push_back(set.get());
				}
				for(auto& [_, pc] : shader->getPushConstants())
					push_constants.push_back(pc);
			}
			if(!matrices_uniform_buffer)
				Core::log::report(FATAL_ERROR, "Forward Pass : did not found 'matrices' uniform buffer in the forward shaders");
			if(!materialset)
				Core::log::report(FATAL_ERROR, "Forward Pass : did not found the material sets in the forward shader");
		}

		MatricesBuffer mat;
		mat.proj = data.camera->getProj();
		mat.view = data.camera->getView();
		mat.proj[1][1] *= -1;
		matrices_uniform_buffer->getBuffer()->setData(sizeof(mat), &mat);

		for(const RenderCommandData& command : data.command_queue)
		{
			auto material = MaterialLibrary::get().getMaterial(command.material);
			material->updateDescriptors(*materialset, rebuildPass);
			sets.push_back(material->_set.get());
			vkCmdBindDescriptorSets(renderer.getActiveCmdBuffer().get(), pipeline->getPipelineBindPoint(), pipeline->getPipelineLayout(), 0, sets.size(), sets.data(), 0, nullptr);

			push_constants[0].setData(&command.transform);
			for(auto& pc : push_constants)
				pc.bind(renderer.getActiveCmdBuffer().get(), pipeline->getPipelineLayout());
	
			command.mesh->draw(renderer);
			sets.pop_back();
		}
		pipeline->endPipeline(renderer.getActiveCmdBuffer());
	}

	void ForwardPass::skyboxPass(RendererComponent& renderer, const ForwardSkyboxData& data, bool rebuildPass)
	{
		/*
		if(!scene->_camera || !scene->_skybox)
            return;

		auto renderer = scene->_renderer;

		// caches
		static Shader::Uniform matrices_uniform_buffer;
		static ShaderID fragment_shader = nullshader;

		if(scene != _scene_cache && (_scene_cache == nullptr || !std::equal(scene->_skybox_shaders.begin(), scene->_skybox_shaders.end(), _scene_cache->_skybox_shaders.begin())))
		{
			_forward_data.descriptor_sets.clear();
			_forward_data.push_constants.clear();
			for(ShaderID id : _forward_data.shaders)
			{
				auto shader = ShadersLibrary::get().getShader(id);
				int material_set = -1;
				if(shader->getType() == VK_SHADER_STAGE_FRAGMENT_BIT)
				{
					fragment_shader = id;
					if(shader->getImageSamplers().count("u_albedo_map"))
						material_set = shader->getImageSamplers()["u_albedo_map"].getSet();
				}
				int i = 0;
				for(DescriptorSet& set : shader->getDescriptorSets())
				{
					if(i != material_set)
						_forward_data.descriptor_sets.push_back(set.get());
					i++;
				}
				if(shader->getUniforms().size() > 0)
				{
					if(shader->getUniforms().count("matrices"))
						matrices_uniform_buffer = shader->getUniforms()["matrices"];
				}
				for(auto& [name, pc] : shader->getPushConstants())
					_forward_data.push_constants.push_back(pc);
			}
		}

		if(fragment_shader == nullshader)
			Core::log::report(FATAL_ERROR, "Scene Renderer : no fragment shader given (wtf)");
        m_SkyboxDescriptorSet->SetTexture("u_CubeMap", m_CubeMap, 0, TextureType::CUBE);
        m_SkyboxDescriptorSet->Update();

		PipelineDesc pipeline_desc;
		pipeline_desc.shaders = _forward_data.shaders;
		pipeline_desc.clear_target = true;
		pipeline_desc.clear_color = { 0.f, 0.f, 0.f, 1.f };
		pipeline_desc.swapchain = (_forward_data.render_texture == nulltexture);
		pipeline_desc.depth = &_forward_data.depth;
		pipeline_desc.render_targets[0] = _forward_data.render_texture;
		pipeline_desc.culling = VK_CULL_MODE_BACK_BIT;

		auto pipeline = _pipelines_manager.getPipeline(*renderer, pipeline_desc);
		if(pipeline == nullptr || !pipeline->bindPipeline(renderer->getActiveCmdBuffer()))
			return;

        auto commandBuffer = Renderer::GetMainSwapChain()->GetCurrentCommandBuffer();
        auto pipeline      = Graphics::Pipeline::Get(pipelineDesc);
        pipeline->Bind(commandBuffer);

        auto set = m_SkyboxDescriptorSet.get();
        Renderer::BindDescriptorSets(pipeline.get(), commandBuffer, 0, &set, 1);
        Renderer::DrawMesh(commandBuffer, pipeline.get(), m_ScreenQuad);

        pipeline->End(commandBuffer);
		*/
	}

	void ForwardPass::destroy()
	{
		_pipelines_manager.clearCache();
	}
}
