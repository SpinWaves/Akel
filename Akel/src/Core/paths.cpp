// This file is a part of Akel
// Authors : @kbz_8
// Created : 12/08/2022
// Updated : 12/08/2022

#include <Core/core.h>

namespace Ak::Core
{
	std::string Paths::logDirPath()
	{
		return log::getLogPath();
	}
}
