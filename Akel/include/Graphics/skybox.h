// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/03/2023
// Updated : 01/11/2023

#ifndef __AK_SKYBOX__
#define __AK_SKYBOX__

#include <Akpch.h>
#include <Renderer/Images/cubemap_library.h>

namespace Ak
{
	struct SkyboxDesc
	{
		std::filesystem::path front;
		std::filesystem::path back;
		std::filesystem::path top;
		std::filesystem::path bottom;
		std::filesystem::path left;
		std::filesystem::path right;
	};

	class AK_API Skybox
	{
		public:
			Skybox() = default;
			Skybox(const SkyboxDesc& description);
			Skybox(const std::filesystem::path& file);
			inline operator bool() const noexcept { return _cubemap != nullcubemap; }
			inline const CubemapID getCubemapID() const noexcept { return _cubemap; }
			~Skybox() = default;

		private:
			CubemapID _cubemap = nullcubemap;
	};
}

#endif
