// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/12/2022
// Updated : 14/02/2023

#include <Renderer/Images/texture.h>
#include <Scene/scene.h>
#include <Renderer/rendererComponent.h>
#include <Renderer/Buffers/vk_ubo.h>
#include "shader_loader.h"
#include <Graphics/builtin_shaders.h>

namespace Ak
{
	struct MatricesBuffer
	{
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	Scene::Scene(fString name) :
		_name(std::move(name)), _entity_manager(create_Unique_ptr<EntityManager>()),
		_loader(create_Unique_ptr<ShaderLoader>()), _camera(nullptr)
	{
		_loader->init();
	}

	Entity createEntity()
	{
		return _entity_manager->create();
	}

	Entity createEntity(const std::string& name)
	{
		return _entity_manager->create(name);
	}

	void Scene::onAttach(RendererComponent* renderer, uint32_t id) noexcept
	{
		_id = id;
		_renderer = renderer;

		std::vector<Texture*> textures;
		for(Entity2D& ent : _2D_entities)
			if(!ent._texture_path.empty())
				textures.push_back(&ent.getTexture());
		for(Entity3D& ent : _3D_entities)
			if(!ent._texture_path.empty())
				textures.push_back(&ent.getTexture());

		if(_shaders.empty())
		{
			_shaders.push_back(std::move(_loader->loadShader(shaderlang::nzsl, std::string_view{default_vertex_shader})));
			_shaders.push_back(std::move(_loader->loadShader(shaderlang::nzsl, std::string_view{default_fragment_shader})));
		}

		_pipeline.init(*_renderer, _shaders, std::vector<Ak::Shader::VertexInput>{ {
				{ Vertex::getBindingDescription() },
				{ Vertex::getAttributeDescriptions()[0], Vertex::getAttributeDescriptions()[1], Vertex::getAttributeDescriptions()[2] },
		} }, std::move(textures), VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_POLYGON_MODE_FILL, VK_CULL_MODE_NONE, VK_FRONT_FACE_CLOCKWISE);
	}

	void Scene::onRender()
	{
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)_renderer->getSwapChain()._swapChainExtent.width;
		viewport.height = (float)_renderer->getSwapChain()._swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(_renderer->getActiveCmdBuffer().get(), 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = _renderer->getSwapChain()._swapChainExtent;
		vkCmdSetScissor(_renderer->getActiveCmdBuffer().get(), 0, 1, &scissor);

		_pipeline.bindPipeline(_renderer->getActiveCmdBuffer());

		std::vector<VkDescriptorSet> sets;
	
		for(Shader& shader : _pipeline.getShaders())
		{
			for(DescriptorSet& set : shader.getDescriptorSets())
				sets.push_back(set.get());
			if(shader.getUniforms().size() > 0)
			{
				if(shader.getUniforms().count("matrices"))
				{
					MatricesBuffer mat;
					mat.proj = _camera->getProj();
					mat.model = _camera->getView();
					mat.view = Matrixes::get_matrix(matrix::view);

					shader.getUniforms()["matrices"].getBuffer()->setData(sizeof(mat), &mat);
				}
			}
		}
		vkCmdBindDescriptorSets(_renderer->getActiveCmdBuffer().get(), _pipeline.getPipelineBindPoint(), _pipeline.getPipelineLayout(), 0, sets.size(), sets.data(), 0, nullptr);
	}

	void Scene::onUpdate(float timestep)
	{
		Maths::Vec2i win_size = _renderer->getWindow()->size;
		_camera->update(win_size.X / win_size.Y);
	}

	void Scene::onEvent(Input& input)
	{
		_camera->onEvent(input);
	}

	void Scene::_loadCustomShader(shaderlang lang, std::filesystem::path path)
	{
		_shaders.push_back(std::move(_loader->loadShader(lang, std::move(path))));
	}

	void Scene::onQuit()
	{
		_loader->destroy();
		_pipeline.destroy();
	}

	Scene::~Scene() {}
}
