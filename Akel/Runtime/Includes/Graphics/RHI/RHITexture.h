// Copyright (C) 2025 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef AK_RHI_TEXTURE_H
#define AK_RHI_TEXTURE_H

#include <Graphics/PreCompiled.h>
#include <Graphics/RHI/Enums.h>
#include <Maths/Vec2.h>

namespace Ak
{
	class AK_GRAPHICS_API RHITexture
	{
		public:
			RHITexture(TextureDimension dims, TextureFormat format, TextureUsage usage, Vec2ui size, std::uint32_t depth, std::uint8_t level_count);

			AK_FORCEINLINE TextureDimension GetDimensions() const noexcept { return m_dims; }
			AK_FORCEINLINE TextureFormat GetFormat() const noexcept { return m_format; }
			AK_FORCEINLINE TextureUsage GetUsage() const noexcept { return m_usage; }
			AK_FORCEINLINE Vec2ui GetSize() const noexcept { return m_size; }
			AK_FORCEINLINE std::uint32_t GetDepth() const noexcept { return m_depth; }
			AK_FORCEINLINE std::uint8_t GetLevelCount() const noexcept { return m_level_count; }

			virtual ~RHITexture() = default;

		protected:
			TextureDimension m_dims;
			TextureFormat m_format;
			Vec2ui m_size;
			TextureUsage m_usage;
			std::uint32_t m_depth;
			std::uint8_t m_level_count;
	};
}

#endif
