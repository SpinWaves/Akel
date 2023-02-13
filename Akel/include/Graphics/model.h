// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 13/02/2023

#ifndef __AK_MODEL__
#define __AK_MODEL__

#include <Akpch.h>
#include <Graphics/mesh.h>

namespace Ak
{
	class AK_API Model
	{
		friend class Scene;

		public:
			Model() = default;
			Model(std::filesystem::path file);
			Model(const Mesh& mesh);
			Model(Mesh&& mesh);

			inline const std::vector<Mesh>& getMeshes() { return _meshes; }

			virtual ~Model() = default;

		private:
			void load();
			void loadOBJ();
			void loadGLTF();

			std::vector<Mesh> _meshes;
			std::filesystem::path _file;
	};
}

#endif
