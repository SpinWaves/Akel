// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/02/2023
// Updated : 30/05/2023

#ifndef __AK_MODEL__
#define __AK_MODEL__

#include <Akpch.h>
#include <Graphics/mesh.h>
#include <Graphics/material_library.h>

namespace Ak
{
	class AK_API Model
	{
		friend class ModelAttribute;

		public:
			Model() = default;
			Model(std::filesystem::path file);
			Model(const Mesh& mesh);
			Model(Mesh&& mesh);

			inline void setMaterial(MaterialID material) noexcept { _material = material; }
			inline MaterialID getMaterial() const noexcept { return _material; }

			inline const Mesh& getMesh() const { return _mesh; }
			inline const std::filesystem::path& getFile() const { return _file; }

			void destroy() noexcept;

			~Model() = default;

		private:
			void load();
			void loadOBJ();
			void loadGLTF();

			Mesh _mesh;
			std::filesystem::path _file;
			MaterialID _material = nullmaterial;
	};
}

#endif
