// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/03/2022
// Updated : 05/03/2022

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
        
        color.SET(((col_val & R_MASK) >> 24) / 0xFF, ((col_val & G_MASK) >> 16) / 0xFF, ((col_val & B_MASK) >> 8) / 0xFF, ((col_val & A_MASK)) / 0xFF);

        switch(model)
        {
            case Models::quad :
                __data.vertexData = {
                    Vertex2D{position, color},
                    Vertex2D{{position.X + scale.X, position.Y}, color},
                    Vertex2D{{position.X + scale.X, position.Y + scale.Y}, color},
                    Vertex2D{{position.X, position.Y + scale.Y}, color}
                };
                __data.indexData = {0, 1, 2, 2, 3, 0};
            break;

            case Models::cube : break;

            default : Core::log::report(ERROR, "Entity 2D : bad model"); break;
        }
    }
}
