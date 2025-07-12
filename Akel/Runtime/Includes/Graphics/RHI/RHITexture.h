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
			RHITexture(TextureType type, TextureFormat format, TextureFlags flags, Vec2ui size, std::uint32_t depth, std::uint8_t level_count);

			AK_FORCEINLINE TextureType GetType() const noexcept { return m_type; }
			AK_FORCEINLINE TextureFormat GetFormat() const noexcept { return m_format; }
			AK_FORCEINLINE TextureFlags GetFlags() const noexcept { return m_flags; }
			AK_FORCEINLINE Vec2ui GetSize() const noexcept { return m_size; }
			AK_FORCEINLINE std::uint32_t GetDepth() const noexcept { return m_depth; }
			AK_FORCEINLINE std::uint8_t GetLevelCount() const noexcept { return m_level_count; }

			virtual ~RHITexture() = default;

		protected:
			TextureType m_type;
			TextureFormat m_format;
			Vec2ui m_size;
			TextureFlags m_flags;
			std::uint32_t m_depth;
			std::uint8_t m_level_count;
	};
}

#endif
