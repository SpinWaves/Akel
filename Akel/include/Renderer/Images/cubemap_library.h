// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/09/2023
// Updated : 06/09/2023

#ifndef __AK_CUBEMAP_LIBRARY__
#define __AK_CUBEMAP_LIBRARY__

#include <Akpch.h>
#include <Utils/selfInstance.h>
#include <Renderer/Images/cubemap.h>

namespace Ak
{
	using CubemapID = uint32_t;
	constexpr CubemapID nullcubemap = 0;

	class AK_API CubemapLibrary : public SelfInstance<CubemapLibrary>
	{
		public:
			CubemapLibrary() = default;

			std::shared_ptr<Cubemap> getCubemap(CubemapID id);
			CubemapID addCubemapToLibrary(const std::filesystem::path& cubemap);
			CubemapID addCubemapToLibrary(std::shared_ptr<Cubemap> cubemap);
			void removeCubemapFromLibrary(CubemapID id);

			void clearLibrary();

			~CubemapLibrary() = default;

		private:
			std::unordered_map<CubemapID, std::shared_ptr<Cubemap>> _cache;
			CubemapID _current_id = 1;
	};
}

#endif
