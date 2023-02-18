// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 18/02/2023

#include <Graphics/mesh.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	{
		_vertex_buffer.create(vertices.size() * sizeof(Vertex), vertices.data());
		_index_buffer.create(indices.size() * sizeof(uint32_t), indices.data());
	}

	void Mesh::draw(RendererComponent& renderer)
	{
		_index_buffer.bind(renderer);
		_vertex_buffer.bind(renderer);
		vkCmdDrawIndexed(renderer.getActiveCmdBuffer().get(), static_cast<uint32_t>(_index_buffer.getSize() / sizeof(uint32_t)), 1, 0, 0, 0);
	}

	void Mesh::destroy()
	{
		_vertex_buffer.destroy();
		_index_buffer.destroy();
	}
}
