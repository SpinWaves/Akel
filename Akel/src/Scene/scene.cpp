// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/12/2022
// Updated : 07/12/2022

#include <Scene/scene.h>
#include <Platform/window.h>
#include <Graphics/matrixes.h>
#include <Renderer/Buffers/vk_ubo.h>

namespace Ak
{
	struct MatrixesBuffer
	{
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	Scene::Scene(fString name, WindowComponent* window) : _name(std::move(name)), _window(window)
	{
		if(window == nullptr)
			Core::log::report(FATAL_ERROR, "Scene '%s' : wrong window pointer", name.c_str());
	}

	void Scene::onAttach(uint32_t id) noexcept
	{
		_id = id;
		_pipeline.init(_shaders, std::vector<Ak::Shader::VertexInput>{ {
				{ Vertex2D::getBindingDescription() },
				{ Vertex2D::getAttributeDescriptions()[0], Vertex2D::getAttributeDescriptions()[1] }
		} });
	}

	void Scene::add_2D_entity(Entity2D entity)
	{
		entity.initBuffers();
		_2D_entities.push_back(std::move(entity));
	}

	void Scene::onPreRender()
	{
		_pipeline.bindPipeline(Render_Core::get().getActiveCmdBuffer());

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)Render_Core::get().getSwapChain()._swapChainExtent.width;
		viewport.height = (float)Render_Core::get().getSwapChain()._swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(Render_Core::get().getActiveCmdBuffer().get(), 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = Render_Core::get().getSwapChain()._swapChainExtent;
		vkCmdSetScissor(Render_Core::get().getActiveCmdBuffer().get(), 0, 1, &scissor);
	}

	void Scene::onRender2D()
	{
		Matrixes::ortho(0, 0, _window->size.X, _window->size.Y);

        for(Entity2D& ent : _2D_entities)
		{
			ent._vbo.bind();
			ent._ibo.bind();

			vkCmdDrawIndexed(Render_Core::get().getActiveCmdBuffer().get(), static_cast<uint32_t>(ent._ibo.getSize() / sizeof(uint32_t)), 1, 0, 0, 0);
		}

		for(Shader* shader : _pipeline.getShaders())
		{
			if(shader->getUniforms().has("matrixes"))
			{
				MatrixesBuffer mat;
				mat.proj = Matrixes::get_matrix(matrix::proj);
				mat.model = Matrixes::get_matrix(matrix::model);
				mat.view = Matrixes::get_matrix(matrix::view);

				shader->getUniforms()["matrixes"].getBuffer()->setDynamicData(sizeof(mat), &mat);
			}
		}
	}

	void Scene::onRender3D()
	{

	}

	void Scene::onQuit()
	{
		for(auto entity : _2D_entities)
			entity.destroy();
		_pipeline.destroy();
	}
}
