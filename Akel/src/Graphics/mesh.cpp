// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 02/12/2023

#include <Graphics/mesh.h>
#include <Renderer/rendererComponent.h>

namespace Ak
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	{
		_vertex_buffer.create(vertices.size() * sizeof(Vertex), vertices.data());
		_index_buffer.create(indices.size() * sizeof(uint32_t), indices.data());
		_is_init = true;
	}

	void Mesh::init(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
	{
		if(_is_init)
			return;
		_vertex_buffer.create(vertices.size() * sizeof(Vertex), vertices.data());
		_index_buffer.create(indices.size() * sizeof(uint32_t), indices.data());
		_is_init = true;
	}

	void Mesh::draw(RendererComponent& renderer) const
	{
		if(!_is_init)
			return;
		_vertex_buffer.bind(renderer);
		_index_buffer.bind(renderer);
		vkCmdDrawIndexed(renderer.getActiveCmdBuffer().get(), static_cast<uint32_t>(_index_buffer.getSize() / sizeof(uint32_t)), 1, 0, 0, 0);
	}

	void Mesh::destroy()
	{
		_vertex_buffer.destroy();
		_index_buffer.destroy();
		_is_init = false;
	}
}
