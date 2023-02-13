// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 13/02/2023

#ifndef __AK_MESH__
#define __AK_MESH__

#include <Akpch.h>
#include <Graphics/vertex.h>
#include <Renderer/Buffers/vk_vbo.h>
#include <Renderer/Buffers/vk_ibo.h>

namespace Ak
{
	class AK_API Mesh
	{
		public:
			Mesh() = default;
			Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

			virtual ~Mesh() = default;

		private:
			std::vector<Vertex> _vertices;
			std::vector<uint32_t> _indices;
			VBO _vertex_buffer;
			IBO _index_buffer;
	};
}

#endif
