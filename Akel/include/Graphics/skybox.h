// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/03/2023
// Updated : 29/03/2023

#ifndef __AK_SKYBOX__
#define __AK_SKYBOX__

#include <Akpch.h>

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
			Skybox(SkyboxDesc description);

			~Skybox();

		private:
	};
}

#endif
