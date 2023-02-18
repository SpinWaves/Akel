// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 18/02/2023

#include <Graphics/model.h>
#include <Core/log.h>
#include <Core/Memory/sharedPtrWrapper.h>

namespace Ak
{
	Model::Model(std::filesystem::path file) : _file(std::move(file)) {}

	Model::Model(const Mesh& mesh)
	{
		_meshes.push_back(create_shared_ptr_w<Mesh>(mesh));
	}

	Model::Model(Mesh&& mesh)
	{
		_meshes.push_back(create_shared_ptr_w<Mesh>(std::move(mesh)));
	}

	void Model::load()
	{
		if(_file.empty())
			return;
		if(!std::filesystem::exists(_file))
			Core::log::report(FATAL_ERROR, "Model : failed to load file '%s'", _file.c_str());

		if(_file.extension() == ".obj")
			loadOBJ();
		else if(_file.extension() == ".gltf")
			loadGLTF();
		else
			Core::log::report(FATAL_ERROR, "Model : unsupported model file type '%s'", _file.c_str());

		#ifdef AK_DEBUG
			Core::log::report(MESSAGE, "Model : loaded file '%s'", _file.c_str());
		#endif
	}

	void Model::loadOBJ()
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if(!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _file.c_str()))
		{
			if(!warn.empty())
				Core::log::report(WARNING, "Model : warning while loading obj file : %s", warn.c_str());
			if(!err.empty())
				Core::log::report(FATAL_ERROR, "Model : error while loading obj file : %s", err.c_str());
		}

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

				vertex.color = {1.0f, 1.0f, 1.0f};

				vertices.push_back(vertex);
				indices.push_back(indices.size());
			}
		}

		_meshes.push_back(create_shared_ptr_w<Mesh>(std::move(vertices), std::move(indices)));
	}

	void Model::loadGLTF()
	{

	}

	Model::~Model()
	{
		for(auto mesh : _meshes)
			mesh->destroy();
	}
}
