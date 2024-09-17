// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

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

