// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Graphics/RHI/RHITexture.h>

namespace Ak
{
	RHITexture::RHITexture(const TextureDescription& description)
		: m_dims(description.dimension), m_format(description.format), m_size(description.size), m_usage(description.usage), m_depth(description.depth), m_level_count(description.level_count)
	{
	}
}
