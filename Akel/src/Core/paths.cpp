// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2022
// Updated : 04/06/2023

#include <Core/core.h>

namespace Ak::Core
{
	std::filesystem::path Paths::logDirPath()
	{
		return log::getLogPath();
	}
}
