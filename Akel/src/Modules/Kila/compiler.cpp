// This file is a part of Akel
// Authors : @kbz_8
// Created : 29/10/2022
// Updated : 03/11/2022

#include <Modules/Kila/file.h>
#include <Modules/Kila/compiler.h>

namespace Ak::Kl
{
	std::string Compiler::loadFile(const std::string& path)
	{
		File f(path.c_str());
		std::string ret;
		while(!f.is_eof())
			ret.push_back((char)f());
		return ret;
	}
}

