// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/01/2023
// Updated : 24/05/2023

#include <Platform/resourceManager.h>

namespace Ak
{
	Res::Res()
	{
		_main_path = Ak::Core::getMainDirPath() + "Resources/";
	}

	std::filesystem::path Res::getTexturesPath() noexcept
	{
		if(!_is_enabled)
			return {};
		return _main_path / "Textures/";
	}
	
	std::filesystem::path Res::getMeshesPath() noexcept
	{
		if(!_is_enabled)
			return {};
		return _main_path / "Meshes/";
	}
	
	std::filesystem::path Res::getScriptsPath() noexcept
	{
		if(!_is_enabled)
			return {};
		return _main_path / "Scripts/";
	}

	std::filesystem::path Res::getScenesPath() noexcept
	{
		if(!_is_enabled)
			return {};
		return _main_path / "Scenes/";
	}
	
	std::filesystem::path Res::getSoundsPath()  noexcept
	{
		if(!_is_enabled)
			return {};
		return _main_path / "Sounds/";
	}

	void Res::createFileSystem()
	{
		std::filesystem::create_directory(_main_path);
		std::filesystem::create_directory(getTexturesPath());
		std::filesystem::create_directory(getMeshesPath());
		std::filesystem::create_directory(getScriptsPath());
		std::filesystem::create_directory(getScenesPath());
		std::filesystem::create_directory(getSoundsPath());
	}
}
