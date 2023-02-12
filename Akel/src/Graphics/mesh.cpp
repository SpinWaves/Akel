// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 12/02/2023

#include <Graphics/mesh.h>

namespace Ak
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) : _vertices(vertices), _indices(indices)
	{
		_vertex_buffer.create(_vertices.size() * sizeof(Vertex));
		_vertex_buffer.setData(_vertex_buffer.getSize(), _vertices.data());

		_index_buffer.create(_indices.size() * sizeof(uint32_t));
		_index_buffer.setData(_index_buffer.getSize(), _indices.data());
	}
}
