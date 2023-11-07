// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 07/11/2023

#include <Renderer/scene_renderer.h>
#include <Renderer/rendererComponent.h>
#include <Scene/Attributes/attributes.h>
#include <Scene/Cameras/base_camera.h>
#include <Scene/entity.h>
#include <Renderer/Buffers/vk_ubo.h>
#include <Renderer/Images/texture_library.h>

namespace Ak
{
	struct MatricesBuffer
	{
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	SceneRenderer::SceneRenderer() : _forward_pass() {}

	void SceneRenderer::init(SceneRendererSettings settings)
	{
		_settings = std::move(settings);
	}

	void SceneRenderer::render(Scene* scene)
	{
		auto renderer = scene->_renderer;

		if(scene == nullptr)
			return;

		bool rebuild = _scene_cache != scene;
		ForwardPassDescription forward_desc;

		if(_settings.geometries) // TODO : do not update command queues if scenes entities haven't been modified
		{
			if(_scene_cache != scene)
			{
				_forward_data.shaders.clear();
				for(ShaderID id : scene->_forward_shaders)
					_forward_data.shaders.push_back(id);
				if(_forward_data.depth() != VK_NULL_HANDLE)
					_forward_data.depth.destroy();
				if(_forward_data.render_texture != nulltexture)
				{
					std::shared_ptr<Texture> tex = TextureLibrary::get().getTexture(_forward_data.render_texture);
					_forward_data.depth.create(*scene->_renderer, tex->getWidth(), tex->getHeight());
				}
				else
					_forward_data.depth.create(*scene->_renderer, renderer->getSwapChain().getExtent().width, renderer->getSwapChain().getExtent().height);
			}

			if(scene->_renderer->isFrameBufferResizeRequested() && _forward_data.render_texture == nulltexture)
			{
				if(_forward_data.depth() != VK_NULL_HANDLE)
					_forward_data.depth.destroy();
				_forward_data.depth.create(*scene->_renderer, renderer->getSwapChain().getExtent().width, renderer->getSwapChain().getExtent().height);
			}

			_forward_data.command_queue.clear();
			auto world = scene->getRegistry().group<ModelAttribute>(entt::get<TransformAttribute>);
			for(auto e : world)
			{
				const ModelAttribute& model = world.get<ModelAttribute>(e);
				const TransformAttribute& trans = world.get<TransformAttribute>(e);

				RenderCommandData command;
				command.mesh = &const_cast<Mesh&>(model.model.getMesh());
				command.material = model.model.getMaterial();
				command.transform = trans.processTransform();

				_forward_data.command_queue.push_back(std::move(command));
			}
			_forward_data.camera = scene->getCamera();
			forward_desc.fdata = &_forward_data;
		}
		if(_scene_cache != scene)
			_scene_cache = scene;

		_forward_pass.process(*renderer, forward_desc, rebuild);
	}
/*
	void SceneRenderer::skyboxPass(Scene* scene)
	{
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
	}
*/
	void SceneRenderer::destroy()
	{
        vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		_forward_data.depth.destroy();
		_forward_pass.destroy();
	}
}
