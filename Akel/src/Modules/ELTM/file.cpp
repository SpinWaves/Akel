// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/08/2022
// Updated : 27/08/2022

#include "file.h"
#include "ELTMerrors.h"

namespace Ak
{
	File::File(const char* path) : _path(path)
	{
		_fp = std::fopen(path, "rt");
		if(!_fp)
			file_not_found_error(path, "", -1).expose();
	}

	File::~File()
	{
		if(_fp)
			std::fclose(_fp);
	}
}

