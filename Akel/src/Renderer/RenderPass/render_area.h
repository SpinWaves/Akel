// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_RENDER_AREA__
#define __AK_VK_RENDER_AREA__

#include <Akpch.h>
#include <Maths/vec2.h>

namespace Ak
{
	class RenderArea
	{
		public:
			explicit RenderArea(const Maths::Vec2<uint32_t>& extent = {}, const Maths::Vec2<int32_t>& offset = {}) : _extent(extent), _offset(offset) {}

			bool operator==(const RenderArea &rhs) const { return _extent == rhs._extent && _offset == rhs._offset; }
			bool operator!=(const RenderArea &rhs) const { return !operator==(rhs); }

			inline const Maths::Vec2<uint32_t>& getExtent() const noexcept { return _extent; }
			inline void setExtent(const Vector2ui &extent) noexcept { _extent = extent; }

			inline const Maths::Vec2<int32_t>& getOffset() const noexcept { return _offset; }
			inline void setOffset(const Maths::Vec2<int32_t>& offset) noexcept { _offset = offset; }

			inline float getAspectRatio() const noexcept { return _aspectRatio; }
			inline void setAspectRatio(float aspectRatio) noexcept { _aspectRatio = aspectRatio; }

		private:
			Maths::Vec2<uint32_t> _extent;
			Maths::Vec2<int32_t> _offset;
			float _aspectRatio = 1.0f;
	};
}

#endif // __AK_VK_RENDER_AREA__
