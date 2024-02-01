// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/08/2022
// Updated : 01/02/2024

#include <Plugins/ELTM/File.h>
#include <Plugins/ELTM/Errors.h>

namespace Ak
{
	File::File(const char* path) : m_path(path)
	{
		m_fp = std::fopen(path, "rt");
		if(!m_fp)
			FileNotFoundError(path, "", -1).Expose();
	}

	File::~File()
	{
		if(m_fp)
			std::fclose(m_fp);
	}
}

