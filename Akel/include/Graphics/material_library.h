// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/02/2023
// Updated : 05/11/2023

#ifndef __AK_MATERIAL_LIBRARY__
#define __AK_MATERIAL_LIBRARY__

#include <Akpch.h>
#include <Utils/selfInstance.h>
#include <Graphics/material.h>

namespace Ak
{
	using MaterialID = uint32_t;
	constexpr MaterialID nullmaterial = 0;

	class AK_API MaterialLibrary : public SelfInstance<MaterialLibrary>
	{
		friend class ForwardPass;

		public:
			MaterialLibrary() = default;

			std::shared_ptr<Material> getMaterial(MaterialID id);
			MaterialID addMaterialToLibrary(std::shared_ptr<Material> material);
			MaterialID addMaterialToLibrary(MaterialDesc material);
			void removeMaterialFromLibrary(MaterialID id);

			void clearLibrary();

			~MaterialLibrary() = default;

		private:
			void setNullMaterial(std::shared_ptr<Material> mat);

			std::unordered_map<MaterialID, std::shared_ptr<Material>> _cache;
			MaterialID _current_id = 1;
	};

	inline MaterialID addMaterialToLibrary(std::shared_ptr<Material> mat) { return MaterialLibrary::get().addMaterialToLibrary(std::move(mat)); }
	inline MaterialID addMaterialToLibrary(MaterialDesc mat) { return MaterialLibrary::get().addMaterialToLibrary(std::move(mat)); }
}

#endif
