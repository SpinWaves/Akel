// This file is a part of Akel
// Authors : @kbz_8
// Created : 09/02/2023
// Updated : 29/03/2023

#ifndef __AK_CUBEMAP__
#define __AK_CUBEMAP__

#include <Akpch.h>
#include "vk_image.h"

namespace Ak
{
	struct CubeMapParts
	{
		std::filesystem::path top;
		std::filesystem::path bottom;
		std::filesystem::path left;
		std::filesystem::path right;
		std::filesystem::path front;
		std::filesystem::path back;
	};

	using json = nlohmann::json;
	class AK_API CubeMap : public Image
	{
		public:
			CubeMap(std::filesystem::path cube_map_file);
			CubeMap(CubeMapParts parts, std::string name);

		private:
			void load() noexcept;

			std::filesystem::path _file;
			json _json;
	};
}

#endif
