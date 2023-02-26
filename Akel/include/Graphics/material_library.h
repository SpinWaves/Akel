// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/02/2023
// Updated : 26/02/2023

#ifndef __AK_MATERIAL_LIBRARY__
#define __AK_MATERIAL_LIBRARY__

#include <Akpch.h>
#include <Utils/selfInstance.h>
#include <Graphics/material.h>

namespace Ak
{
	using MaterialID = uint32_t;
	constexpr MaterialId nullmaterial = 0;

	class AK_API MaterialLibrary : public SelfInstance<MaterialLibrary>
	{
		public:
			MaterialLibrary() = default;

			std::shared_ptr<Material> getMaterial(MaterialID id);
			MaterialID addMaterialToLibrary(std::shared_ptr<Material> material);
			void removeMaterialFromLibrary(MaterialID id);

			void clearLibrary();

			~MaterialLibrary() = default;

		private:
			std::unordered_map<MaterialID, std::shared_ptr<Material>> _cache;
			MaterialID _current_id = 1;
	};
}

#endif
