// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 06/11/2023

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
			Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

			void init(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
			void draw(class RendererComponent& renderer);
			void destroy();

			~Mesh() = default;

		private:
			C_VBO _vertex_buffer;
			C_IBO _index_buffer;
			bool _is_init = false;
	};
}

#endif
