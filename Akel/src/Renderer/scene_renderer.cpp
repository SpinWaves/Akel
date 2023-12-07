// This file is a part of Akel
// Authors : @kbz_8
// Created : 15/02/2023
// Updated : 02/12/2023

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
        _forward_pass.init();
	}

	void SceneRenderer::render(Scene* scene)
	{
		auto renderer = scene->_renderer;

		if(scene == nullptr)
			return;

		bool rebuild = _scene_cache != scene;
		ForwardPassDescription forward_desc;

		if(_scene_cache != scene)
		{
			if(_common_forward_data.depth() != VK_NULL_HANDLE)
				_common_forward_data.depth.destroy();
			if(_common_forward_data.render_texture != nulltexture)
			{
				std::shared_ptr<Texture> tex = TextureLibrary::get().getTexture(_common_forward_data.render_texture);
				_common_forward_data.depth.create(*scene->_renderer, tex->getWidth(), tex->getHeight());
			}
			else
				_common_forward_data.depth.create(*renderer, renderer->getSwapChain().getExtent().width, renderer->getSwapChain().getExtent().height);
			_common_forward_data.camera = scene->getCamera();
		}

		if(scene->_renderer->isFrameBufferResizeRequested() && _forward_data.render_texture == nulltexture)
		{
			if(_forward_data.depth() != VK_NULL_HANDLE)
				_forward_data.depth.destroy();
			_forward_data.depth.create(*scene->_renderer, renderer->getSwapChain().getExtent().width, renderer->getSwapChain().getExtent().height);
		}

		if(_settings.geometries) // TODO : do not update command queues if scenes entities haven't been modified
		{
			_forward_data.setCommonData(_common_forward_data);
			if(_scene_cache != scene)
			{
				_forward_data.shaders.clear();
				for(ShaderID id : scene->_forward_shaders)
					_forward_data.shaders.push_back(id);
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
			forward_desc.fdata = &_forward_data;
		}

		if(_settings.skybox)
		{
			_skybox_data.setCommonData(_common_forward_data);
			if(_scene_cache != scene)
			{
				_skybox_data.shaders.clear();
				for(ShaderID id : scene->_skybox_shaders)
					_skybox_data.shaders.push_back(id);
			}
			_skybox_data.cubemap = scene->getSkybox().getCubemapID();
			forward_desc.skydata = &_skybox_data;
		}

		if(_scene_cache != scene)
			_scene_cache = scene;

		_forward_pass.process(*renderer, forward_desc, rebuild);
	}

	void SceneRenderer::destroy()
	{
        vkDeviceWaitIdle(Render_Core::get().getDevice().get());
		_forward_data.depth.destroy();
		_forward_pass.destroy();
	}
}
