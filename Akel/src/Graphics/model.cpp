// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 14/10/2023

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <Graphics/model.h>
#include <Core/log.h>
#include <Core/Memory/akel_shared_ptr.h>

namespace Ak
{
	Model::Model(std::filesystem::path file) : _file(std::move(file)) {}
	Model::Model(const Mesh& mesh) : _mesh(mesh) {}
	Model::Model(Mesh&& mesh) : _mesh(std::move(mesh)) {}

	void Model::load()
	{
		if(_file.empty())
			return;
		std::string file_path = _file.string();
		if(!std::filesystem::exists(_file))
			Core::log::report(FATAL_ERROR, "Model : failed to load file '%s'", file_path.c_str());

		if(_file.extension() == ".obj")
			loadOBJ();
		else if(_file.extension() == ".gltf")
			loadGLTF();
		else
			Core::log::report(FATAL_ERROR, "Model : unsupported model file type '%s'", file_path.c_str());

		Core::log::report(DEBUGLOG, "Model : loaded file '%s'", file_path.c_str());
	}

	void Model::loadOBJ()
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;
		std::string stream_file(_file.string());

		if(!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, stream_file.c_str()))
		{
			if(!warn.empty())
				Core::log::report(WARNING, "Model : warning while loading obj file : %s", warn.c_str());
			if(!err.empty())
				Core::log::report(FATAL_ERROR, "Model : error while loading obj file : %s", err.c_str());
		}
		std::cout << materials.size() << std::endl;

		//std::unordered_map<Vertex, uint32_t> unique_vertices;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for(const auto& shape : shapes)
		{
			for(const auto& index : shape.mesh.indices)
			{
				Vertex vertex{};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.texture_coords = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.color.set(1.0f, 1.0f, 1.0f, 1.0f);
/*
				if(unique_vertices.count(vertex) == 0)
				{
					unique_vertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}
				indices.push_back(unique_vertices[vertex]);
*/
				indices.push_back(vertices.size());
				vertices.push_back(std::move(vertex));
			}
		}
		_mesh.init(std::move(vertices), std::move(indices));
	}

	void Model::loadGLTF()
	{

	}

	void Model::destroy() noexcept
	{
		_mesh.destroy();
	}
}
