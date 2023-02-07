// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2021
// Updated : 01/02/2023

#ifndef __AK_ENTITY__
#define __AK_ENTITY__

#include <Akpch.h>

#include <Maths/maths.h>
#include <Core/profile.h>
#include <Graphics/vertex.h>

#include <Renderer/Buffers/vk_ibo.h>
#include <Renderer/Buffers/vk_vbo.h>
#include <Renderer/Images/texture.h>

enum class Models
{
	quad,
	triangle,
	cube,
};

enum class Colors : uint32_t
{
	red     = 0xFF0000FF,
	blue    = 0x0000FFFF,
	green   = 0x00FF00FF,
	yellow  = 0xFFFF00FF,
	magenta = 0xFF00FFFF,
	purple  = 0x800080FF,
	pink    = 0xFF00F0FF,
	cyan    = 0x00FFFFFF,
	black   = 0x000000FF,
	white   = 0xFFFFFFFF,
	none	= white,
};

namespace Ak
{
	class AK_API Entity3D
	{
		friend class Scene;

		public:
			Entity3D(Models _model, Maths::Vec3<float> _position, Maths::Vec3<float> _scale, Maths::Vec4<float> _color, std::filesystem::path texture = "");
			Entity3D(Models _model, Maths::Vec3<float> _position, Maths::Vec3<float> _scale, Colors color, std::filesystem::path texture = "");

			inline Texture& getTexture() noexcept { return _texture; }
			void destroy() noexcept;

			Models model;
			Maths::Vec3<float> position;
			Maths::Vec3<float> scale;
			Maths::Vec4<float> color;

		private:
			void initBuffers();

			Texture _texture;
			C_VBO _vbo;
			C_IBO _ibo;
			std::filesystem::path _texture_path;
	};

	class AK_API Entity2D
	{
		friend class Scene;

		public:
			Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Maths::Vec4<float> _color, std::filesystem::path texture = "");
			Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Colors color, std::filesystem::path texture = "");

			inline Texture& getTexture() noexcept { return _texture; }

			void destroy() noexcept;

			Models model;
			Maths::Vec2<float> position;
			Maths::Vec2<float> scale;
			Maths::Vec4<float> color;

		private:
			void initBuffers();

			Texture _texture;
			C_VBO _vbo;
			C_IBO _ibo;
			std::filesystem::path _texture_path;
	};
}

#endif // __AK_ENTITY__
