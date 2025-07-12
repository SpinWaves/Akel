// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Graphics/RHI/RHITexture.h>

namespace Ak
{
	RHITexture::RHITexture(TextureType type, TextureFormat format, TextureFlags flags, Vec2ui size, std::uint32_t depth, std::uint8_t level_count)
		: m_type(type), m_format(format), m_size(size), m_flags(flags), m_depth(depth), m_level_count(level_count)
	{
	}
}
