// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/06/2021
// Updated : 05/03/2022

#ifndef __AK_ENTITY__
#define __AK_ENTITY__

#include <Akpch.h>

#include <Maths/maths.h>
#include <Graphics/vertex.h>

enum class Models
{
	quad,
	cube,
};

enum class Colors : uint32_t
{
	red     = 0xFF0000FF,
	blue    = 0x0000FFFF,
	green   = 0x00FF00FF,
	yellow  = 0xFFFF00FF,
	magenta = 0xFF00FFFF,
	purple  = 0xF000FFFF,
	pink    = 0xFF00F0FF,
	cyan    = 0x00FFFFFF,
	black   = 0x000000FF,
	white   = 0xFFFFFFFF,
};

namespace Ak
{

	class Entity3D
	{
		public:
			Entity3D(Models _model, Maths::Vec3<float> _position, Maths::Vec3<float> _scale, Maths::Vec4<float> _color);
			Entity3D(Models _model, Maths::Vec3<float> _position, Maths::Vec3<float> _scale, Colors _color);

			Models model;
			Maths::Vec3<float> position;
			Maths::Vec3<float> scale;
			Maths::Vec4<float> color;

			struct EntityInternalData
			{
				std::vector<Vertex2D> vertexData;
				VkBuffer vertexBuffer;
				VkDeviceMemory vertexBufferMemory;
				std::vector<uint16_t> indexData;
				VkBuffer indexBuffer;
				VkDeviceMemory indexBufferMemory;
			};

			EntityInternalData __data;
	};

	class Entity2D
	{
		public:
			Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Maths::Vec4<float> _color);
			Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Colors color);

			Models model;
			Maths::Vec2<float> position;
			Maths::Vec2<float> scale;
			Maths::Vec4<float> color;

			struct EntityInternalData
			{
				std::vector<Vertex2D> vertexData;
				VkBuffer vertexBuffer;
				VkDeviceMemory vertexBufferMemory;
				std::vector<uint16_t> indexData;
				VkBuffer indexBuffer;
				VkDeviceMemory indexBufferMemory;
			};

			EntityInternalData __data;
	};
}

#endif // __AK_ENTITY__
