// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Core/File.h>
#include <Core/Logs.h>

namespace Ak
{
	File::File(const std::filesystem::path& filepath) : m_filepath(filepath) {}

	File::File(const std::filesystem::path& filepath, std::uint32_t flags) : m_filepath(filepath)
	{
		Open(flags);
	}

	bool File::Open(std::uint32_t flags)
	{
		std::ios_base::openmode mode;
		mode = (flags & FileModeAppend ? mode | std::ios::app : mode);
		mode = (flags & FileModeBinary ? mode | std::ios::binary : mode);
		mode = (flags & FileModeOverride ? mode | std::ios::trunc : mode);
		m_stream.open(m_filepath, mode);
		return m_stream.is_open();
	}

	void File::Close()
	{
		m_stream.close();
		m_filepath.clear();
	}
}
