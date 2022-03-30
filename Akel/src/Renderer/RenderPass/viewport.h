// This file is a part of Akel
// Authors : @kbz_8
// Created : 30/03/2022
// Updated : 30/03/2022

#ifndef __AK_VK_VIEWPORT__
#define __AK_VK_VIEWPORT__

#include <Akpch.h>
#include <Maths/vec2.h>

namespace Ak
{
	class Viewport
	{
		public:
			Viewport() = default;

			explicit Viewport(const Maths::Vec2<uint32_t>& size) : _size(size) {}

			inline const Maths::Vec2<float>& getScale() const noexcept { return _scale; }
			inline void setScale(const Maths::Vec2<float>& scale) noexcept { _scale = scale; }

			inline const std::optional<Maths::Vec2<uint32_t>>& getSize() const noexcept { return _size; }
			inline void setSize(const std::optional<Maths::Vec2<int32_t>>& size) noexcept { _size = size; }

			inline const Maths::Vec2<int32_t>& getOffset() const noexcept { return _offset; }
			inline void setOffset(const Maths::Vec2<int32_t>& offset) noexcept { _offset = offset; }

		private:
			Maths::Vec2<float> _scale = {1.0f, 1.0f};
			std::optional<Maths::Vec2<uint32_t>> _size;
			MAths::Vec2<int32_t> _offset;
	};
}

#endif // __AK_VK_VIEWPORT__
