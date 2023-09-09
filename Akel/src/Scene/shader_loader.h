// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 07/02/2023

#ifndef __AK_SHADER_LOADER__
#define __AK_SHADER_LOADER__

#include <Akpch.h>
#include <Scene/scene.h>
#include <Core/Memory/akel_unique_ptr.h>

namespace Ak
{
	class NzslLoader;
	class KilaLoader;

	class ShaderLoader
	{
		public:
			ShaderLoader() = default;

			void init();
			std::vector<uint32_t> loadShader(shaderlang lang, std::filesystem::path path);
			std::vector<uint32_t> loadShader(shaderlang lang, std::string_view shader);
			void destroy();

			~ShaderLoader() = default;

		private:
			UniquePtr<NzslLoader> _nzsl_loader = nullptr;
			UniquePtr<KilaLoader> _kila_loader = nullptr;
	};

	class NzslLoader
	{
		public:
			NzslLoader();
			
			std::vector<uint32_t> loadShader(std::filesystem::path path);
			std::vector<uint32_t> loadShader(std::string_view shader);
			
			~NzslLoader() = default;

		private:
			std::shared_ptr<nzsl::FilesystemModuleResolver> _resolver;
			nzsl::SpirvWriter _writer;
	};

	class KilaLoader
	{
		public:

		private:
	};
}

#endif
