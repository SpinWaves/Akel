// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/01/2023
// Updated : 24/05/2023

#ifndef __AK_RESOURCE_MANAGER__
#define __AK_RESOURCE_MANAGER__

#include <Akpch.h>
#include <Core/profile.h>
#include <Utils/selfInstance.h>

namespace Ak
{
	class AK_API Res : public SelfInstance<Res>
	{
		friend bool initAkel(AkelInstance*);

		public:
			Res();

			std::filesystem::path getTexturesPath() noexcept;
			std::filesystem::path getMeshesPath() noexcept;
			std::filesystem::path getScriptsPath() noexcept;
			std::filesystem::path getScenesPath() noexcept;
			std::filesystem::path getSoundsPath() noexcept;

			~Res() = default;

		private:
			void createFileSystem();

			std::filesystem::path _main_path;
			bool _is_enabled = true;
	};
}

#endif
