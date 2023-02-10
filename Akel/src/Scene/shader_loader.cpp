// This file is a part of Akel
// Authors : @kbz_8
// Created : 07/02/2023
// Updated : 07/02/2023

#include "shader_loader.h"
#include <Graphics/nzsl_builtin_modules.h>

namespace Ak
{
	void ShaderLoader::init()
	{
		_nzsl_loader = create_Unique_ptr<NzslLoader>();
		_kila_loader = create_Unique_ptr<KilaLoader>();
	}

	std::vector<uint32_t> ShaderLoader::loadShader(shaderlang lang, std::filesystem::path path)
	{
		switch(lang)
		{
			case shaderlang::nzsl: return _nzsl_loader->loadShader(std::move(path));

			default: Core::log::report(ERROR, "Shader Loader : wrong shader language"); break;
		}
		return {};
	}

	std::vector<uint32_t> ShaderLoader::loadShader(shaderlang lang, std::string_view shader)
	{
		switch(lang)
		{
			case shaderlang::nzsl: return _nzsl_loader->loadShader(shader);

			default: Core::log::report(ERROR, "Shader Loader : wrong shader language"); break;
		}
		return {};
	}

	void ShaderLoader::destroy()
	{
		_nzsl_loader.reset();
		_kila_loader.reset();
	}

	NzslLoader::NzslLoader() : _resolver(std::make_shared<nzsl::FilesystemModuleResolver>()) {}

	std::vector<uint32_t> NzslLoader::loadShader(std::filesystem::path path)
	{
		nzsl::Ast::ModulePtr nzsl_module = nzsl::ParseFromFile(path);

		_resolver->RegisterModuleDirectory(path.remove_filename());
		_resolver->RegisterModule(std::string_view{Ak_nzsl::vertex_input});
		_resolver->RegisterModule(std::string_view{Ak_nzsl::vertex_output});
		_resolver->RegisterModule(std::string_view{Ak_nzsl::fragment_output});
		_resolver->RegisterModule(std::string_view{Ak_nzsl::matrices});

		nzsl::ShaderWriter::States states;
		states.shaderModuleResolver = _resolver;

		return _writer.Generate(*nzsl_module, states);
	}

	std::vector<uint32_t> NzslLoader::loadShader(std::string_view shader)
	{
		nzsl::Ast::ModulePtr nzsl_module = nzsl::Parse(shader);

		_resolver->RegisterModule(shader);
		_resolver->RegisterModule(std::string_view{Ak_nzsl::vertex_input});
		_resolver->RegisterModule(std::string_view{Ak_nzsl::vertex_output});
		_resolver->RegisterModule(std::string_view{Ak_nzsl::fragment_output});
		_resolver->RegisterModule(std::string_view{Ak_nzsl::matrices});

		nzsl::ShaderWriter::States states;
		states.shaderModuleResolver = _resolver;

		return _writer.Generate(*nzsl_module, states);
	}
}
