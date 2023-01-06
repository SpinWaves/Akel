// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/03/2022
// Updated : 06/01/2023

#include <Graphics/entity.h>
#include <Core/core.h>

#define R_MASK 0xFF000000
#define G_MASK 0x00FF0000
#define B_MASK 0x0000FF00
#define A_MASK 0x000000FF

namespace Ak
{
	Entity2D::Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Maths::Vec4<float> _color)
	{
	    model = _model;
		position = std::move(_position);
		scale = std::move(_scale);
		color = std::move(_color);
	}

	Entity2D::Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Colors _color)
    {
	    model = _model;
		position = std::move(_position);
		scale = std::move(_scale);
        uint32_t col_val = static_cast<uint32_t>(_color);
        color.SET(static_cast<float>((col_val & R_MASK) >> 24) / 255, static_cast<float>((col_val & G_MASK) >> 16) / 255, static_cast<float>((col_val & B_MASK) >> 8) / 255, static_cast<float>((col_val & A_MASK)) / 255);
    }

	void Entity2D::destroy() noexcept
	{
		_vbo.destroy();
		_ibo.destroy();
	}

	void Entity2D::initBuffers()
	{
        switch(model)
        {
            case Models::quad :
			{
				std::vector<Vertex> vertexData = {
                    {{position.X, position.Y, 0}, color},
                    {{position.X + scale.X, position.Y, 0}, color},
                    {{position.X + scale.X, position.Y + scale.Y, 0}, color},
                    {{position.X, position.Y + scale.Y, 0}, color}
                };

				std::vector<uint32_t> indexData = { 0, 1, 2, 2, 3, 0 };

				_vbo.create(sizeof(Vertex) * vertexData.size(), vertexData.data());
				_ibo.create(sizeof(uint32_t) * indexData.size(), indexData.data());

				break;
			}

            case Models::triangle :
            break;

            default : Core::log::report(ERROR, "Entity 2D : bad model"); break;
        }
	}
}
