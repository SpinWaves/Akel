// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/03/2022
// Updated : 01/02/2023

#include <Graphics/entity.h>
#include <Core/core.h>

#define R_MASK 0xFF000000
#define G_MASK 0x00FF0000
#define B_MASK 0x0000FF00
#define A_MASK 0x000000FF

namespace Ak
{
	Entity3D::Entity3D(Models _model, Maths::Vec3<float> _position, Maths::Vec3<float> _scale, Maths::Vec4<float> _color, std::filesystem::path texture)
	: _texture_path(std::move(texture))
	{
	    model = _model;
		position = std::move(_position);
		scale = std::move(_scale);
		color = std::move(_color);
	}

	Entity3D::Entity3D(Models _model, Maths::Vec3<float> _position, Maths::Vec3<float> _scale, Colors _color, std::filesystem::path texture)
	: _texture_path(std::move(texture))
    {
	    model = _model;
		position = std::move(_position);
		scale = std::move(_scale);
        uint32_t col_val = static_cast<uint32_t>(_color);
        color.SET(static_cast<float>((col_val & R_MASK) >> 24) / 255, static_cast<float>((col_val & G_MASK) >> 16) / 255, static_cast<float>((col_val & B_MASK) >> 8) / 255, static_cast<float>((col_val & A_MASK)) / 255);
    }

	void Entity3D::destroy() noexcept
	{
		_vbo.destroy();
		_ibo.destroy();
		_texture.destroy();
	}

	void Entity3D::initBuffers()
	{
        switch(model)
        {
			case Models::cube:
			{
				const std::vector<Vertex> vertexData = {
					{{position.X, position.Y + scale.Y, position.Z + scale.Z}, 			color, {0.0f, 0.0f}},
					{{position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z},color, {1.0f, 0.0f}},
					{{position.X + scale.X, position.Y, position.Z + scale.Z}, 			color, {1.0f, 1.0f}},
					{{position.X, position.Y, position.Z + scale.Z}, 					color, {0.0f, 1.0f}},
					{{position.X, position.Y + scale.Y, position.Z}, 					color, {1.0f, 0.0f}},
					{{position.X + scale.X, position.Y + scale.Y, position.Z}, 			color, {1.0f, 1.0f}},
					{{position.X + scale.X, position.Y, position.Z}, 					color, {0.0f, 1.0f}},
					{{position.X, position.Y, position.Z,}, 							color, {0.0f, 0.0f}},
					{{position.X, position.Y + scale.Y, position.Z}, 					color, {1.0f, 0.0f}},
					{{position.X, position.Y + scale.Y, position.Z + scale.Z}, 			color, {1.0f, 1.0f}},
					{{position.X, position.Y, position.Z + scale.Z}, 					color, {0.0f, 1.0f}},
					{{position.X, position.Y, position.Z}, 								color, {0.0f, 0.0f}},
					{{position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z},color, {1.0f, 0.0f}},
					{{position.X + scale.X, position.Y + scale.Y, position.Z}, 			color, {1.0f, 1.0f}},
					{{position.X + scale.X, position.Y, position.Z}, 					color, {0.0f, 1.0f}},
					{{position.X + scale.X, position.Y, position.Z + scale.Z}, 			color, {0.0f, 0.0f}},
					{{position.X, position.Y + scale.Y, position.Z}, 					color, {0.0f, 0.0f}},
					{{position.X + scale.X, position.Y + scale.Y, position.Z}, 			color, {1.0f, 0.0f}},
					{{position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z},color, {1.0f, 1.0f}},
					{{position.X, position.Y + scale.Y, position.Z + scale.Z}, 			color, {0.0f, 1.0f}},
					{{position.X, position.Y, position.Y + scale.Z}, 					color, {1.0f, 0.0f}},
					{{position.X + scale.X, position.Y, position.Z + scale.Z}, 			color, {1.0f, 1.0f}},
					{{position.X + scale.X, position.Y, position.Z}, 					color, {0.0f, 1.0f}},
					{{position.X, position.Y, position.Z}, 								color, {0.0f, 0.0f}}
				};

				const std::vector<uint32_t> indexData = {
					0,  1,  2,   2,  3,  0,  // top
					4,  5,  6,   6,  7,  4,  // back
					8,  9, 10,  10, 11,  8,  // left
					12, 13, 14,  14, 15, 12, // front
					16, 17, 18,  18, 19, 16, // right
					20, 21, 22,  22, 23, 20  // bottom
				};

				_vbo.create(sizeof(Vertex) * vertexData.size(), vertexData.data());
				_ibo.create(sizeof(uint32_t) * indexData.size(), indexData.data());

				if(!_texture_path.empty())
					_texture = std::move(loadTextureFromFile(_texture_path));

				break;
			}

            default : Core::log::report(ERROR, "Entity 3D : bad model"); break;
        }
	}
}
